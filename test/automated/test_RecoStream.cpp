#include "include/RecoStream.h"
#include "include/Pub.h"
#include "include/defaults.h"
#include "include/structs.h"
#include "TestData.h"
#include "include/Sub.h"

#include <json/json.h>

#include <string>
#include <iostream>
#include <unistd.h>
#include <complex>
#include "math.h"

using std::complex;
using std::string;
using std::cout;
using std::endl;


class TestRecoStream {
public:
    TestRecoStream();

    // Publishers to send test data.
    string m_pub_host = "*";
    Pub m_pub;
    Sub m_frame_sub;

    // RecoStream to receive data.
    bool m_use_out = true;
    string m_recostream_host = "127.0.0.1";
    RecoStream m_recostream;

    // Testdata to send.
    Json::Value m_startdata;
    Json::Value m_stopdata;
    Json::Value m_abortdata;

    Frame m_framedata;
    Reco m_recdata;

    void init_testdata();

    // Test scenarios
    void test_start();
    void test_frame();
    void test_stop();
    void test_abort();
    void test_rec();
};

TestRecoStream::TestRecoStream() {
    m_pub = Pub(m_pub_host, START_PORT, "");

    if (m_use_out) {
        m_frame_sub = Sub("127.0.0.1", REC_PORT, REC_TOPIC);
    }

    m_recostream = RecoStream(m_recostream_host,
                             m_recostream_host,
                              m_recostream_host,
                             m_recostream_host,
                             m_use_out);

    m_recostream.init_sockets();

    cout << "Sleeping for 5 seconds to allow sockets to properly initialize." << endl;
    sleep(5);
}

void TestRecoStream::init_testdata() {
    cout << "Initializing testdata from TestData.h." << endl;
    m_startdata = get_startdata();
    m_stopdata = get_stopdata();
    m_abortdata = get_abortdata();
    m_framedata = get_framedata();
    m_recdata = get_recdata();
}

void TestRecoStream::test_start() {
    cout << "Testing start event" << endl;
    cout << "\tSetting up socket for sending of start event" << endl;
    m_pub.m_topic = START_TOPIC;
    cout << "\tSleeping for 1 second to allow socket to initialize" << endl;
    sleep(1.0);
    cout << "\tSending start event" << endl;
    m_pub.send_json(m_startdata);
    cout << "\tSleeping for 1 second to allow message to arrive" << endl;
    sleep(1.0);

    assert(m_recostream.something_in_queue());
    assert(m_recostream.has_start_arrived());
    assert(! m_recostream.has_frame_arrived());
    assert(! m_recostream.has_stop_arrived());
    assert(! m_recostream.has_abort_arrived());

    cout << "\tWaiting to receive start event" << endl;
    Json::Value startdata_recv = m_recostream.recv_start();
    cout << "\tStart event received" << endl;
    // Let's see if this works.
    assert(startdata_recv == m_startdata);
    cout << "\tSleeping for 1 socket to allow sending socket to properly close" << endl;
}

void TestRecoStream::test_frame() {
    cout << "Testing frame event" << endl;
    cout << "\tSetting up socket for sending of frame event" << endl;
    m_pub.m_topic = FRAME_TOPIC;
    cout << "\tSleeping for 1 second to allow socket to initialize" << endl;
    sleep(1.0);
    cout << "\tSending frame event" << endl;
    m_pub.send_frame(m_framedata);
    cout << "\tSleeping for 1 second to allow message to arrive" << endl;
    sleep(1.0);

    assert(m_recostream.something_in_queue());
    assert(! m_recostream.has_start_arrived());
    assert(m_recostream.has_frame_arrived());
    assert(! m_recostream.has_stop_arrived());
    assert(! m_recostream.has_abort_arrived());

    cout << "\tWaiting to receive frame event" << endl;
    Frame frame_recv = m_recostream.recv_frame();
    cout << "\tFrame event received" << endl;
    assert(m_framedata.identifier == frame_recv.identifier);
    assert(m_framedata.index == frame_recv.index);
    assert(m_framedata.posx == frame_recv.posx);
    assert(m_framedata.posy == frame_recv.posy);
    assert(m_framedata.shape_y == frame_recv.shape_y);
    assert(m_framedata.shape_x == frame_recv.shape_x);
    assert(m_framedata.dtype == frame_recv.dtype);
    assert(m_framedata.byteorder == frame_recv.byteorder);
    assert(m_framedata.order == frame_recv.order);

    int* data_send = (int*) m_framedata.data;
    int* data_recv = (int*) frame_recv.data;
    for (int i = 0; i < frame_recv.shape_y * frame_recv.shape_x; i++) {
        assert(data_send[i] == data_recv[i]);
    }
}

void TestRecoStream::test_stop() {
    cout << "Testing stop event" << endl;
    cout << "\tSending stop event" << endl;
    cout << "\tSetting up socket for sending of stop event" << endl;
    m_pub.m_topic = STOP_TOPIC;
    cout << "\tSleeping for 1 second to allow socket to initialize" << endl;
    sleep(1.0);
    m_pub.send_json(m_stopdata);
    cout << "\tSleeping for 1 second to allow message to arrive" << endl;
    sleep(1.0);

    assert(m_recostream.something_in_queue());
    assert(! m_recostream.has_start_arrived());
    assert(! m_recostream.has_frame_arrived());
    assert(m_recostream.has_stop_arrived());
    assert(! m_recostream.has_abort_arrived());

    cout << "\tWaiting to receive stop event" << endl;
    Json::Value stopdata_recv = m_recostream.recv_stop();
    cout << "\tStop event received" << endl;
    assert(stopdata_recv == m_stopdata);
}

void TestRecoStream::test_abort() {
    cout << "Testing abort event" << endl;
    cout << "\tSending abort event" << endl;
    cout << "\tSetting up socket for sending of abort event" << endl;
    m_pub.m_topic = ABORT_TOPIC;
    cout << "\tSleeping for 1 second to allow socket to initialize" << endl;
    sleep(1.0);
    m_pub.send_json(m_abortdata);
    cout << "\tSleeping for 1 second to allow message to arrive" << endl;
    sleep(1.0);

    assert(m_recostream.something_in_queue());
    assert(! m_recostream.has_start_arrived());
    assert(! m_recostream.has_frame_arrived());
    assert(! m_recostream.has_stop_arrived());
    assert(m_recostream.has_abort_arrived());

    cout << "\tWaiting to receive abort event" << endl;
    Json::Value abortdata_recv = m_recostream.recv_abort();
    cout << "\tAbort event received" << endl;
    assert(abortdata_recv == m_abortdata);
}


void TestRecoStream::test_rec() {
    cout << "Testing rec event" << endl;
    cout << "\tSending rec event" << endl;
    cout << "\tSleeping for 1 second to allow socket to initialize" << endl;
    sleep(1.0);
    m_recostream.send_rec(m_recdata);
    cout << "\tSleeping for 1 second to allow message to arrive" << endl;
    sleep(1.0);

    cout << "\tWaiting to receive rec event" << endl;
    Reco reco_recv = m_frame_sub.recv_rec();
    cout << "\tRec event received" << endl;
    assert(m_recdata.identifier == reco_recv.identifier);
    assert(m_recdata.pixelsize_y == reco_recv.pixelsize_y);
    assert(m_recdata.pixelsize_x == reco_recv.pixelsize_x);
    assert(m_recdata.shape_y == reco_recv.shape_y);
    assert(m_recdata.shape_x == reco_recv.shape_x);
    assert(m_recdata.dtype == reco_recv.dtype);
    assert(m_recdata.byteorder == reco_recv.byteorder);
    assert(m_recdata.order == reco_recv.order);

    complex<float>* data_send = (complex<float>*) m_recdata.data;
    complex<float>* data_recv = (complex<float>*) reco_recv.data;
    for (int i = 0; i < reco_recv.shape_y * reco_recv.shape_x; i++) {
        complex<float> value_send = data_send[i];
        complex<float> value_recv = data_recv[i];
        assert(abs(value_send.real() - value_recv.real()) < 0.001);
        assert(abs(value_send.imag() - value_recv.imag()) < 0.001);
    }
}

int main() {
    TestRecoStream test_recostream = TestRecoStream();

    test_recostream.init_testdata();
    test_recostream.test_start();
    test_recostream.test_frame();
    test_recostream.test_stop();
    test_recostream.test_abort();
    test_recostream.test_rec();
}
