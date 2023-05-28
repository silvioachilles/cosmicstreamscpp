#include "cosmicstreamscpp/Pub.h"
#include "cosmicstreamscpp/Sub.h"
#include "TestData.h"

#include <string>
#include <iostream>
#include <unistd.h>
#include <cassert>

using std::string;
using std::cout;
using std::endl;


int main() {
    string host_pub = "*";
    int port = 5555;
    string topic = "frame";

    cout << "Setting up FramePub" << endl;
    Pub frame_pub (host_pub, port, topic);

    string host_sub = "127.0.0.1";

    cout << "Setting up FrameSub" << endl;
    Sub frame_sub (host_sub, port, topic);

    cout << "Sleeping for 5 seconds to allow sockets to initialize" << endl;
    sleep(5.0);

    Frame frame = get_framedata();

    cout << "Sending frame" << endl;
    frame_pub.send_frame(frame);
    cout << "\tdone." << endl;

    cout << "Sleeping for 2 seconds" << endl;
    sleep(2.0);
    cout << "Waiting to receive frame" << endl;
    Frame frame_recv = frame_sub.recv_frame();
    cout << "\treceived" << endl;

    assert(frame.identifier == frame_recv.identifier);
    assert(frame.index == frame_recv.index);
    assert(frame.posx == frame_recv.posx);
    assert(frame.posy == frame_recv.posy);
    assert(frame.shape_y == frame_recv.shape_y);
    assert(frame.shape_x == frame_recv.shape_x);
    assert(frame.dtype == frame_recv.dtype);
    assert(frame.byteorder == frame_recv.byteorder);
    assert(frame.order == frame_recv.order);

    // The fact that the datatype is int is hardcoded in the testdata.
    // We make use of that we know it is hardcoded and that it is int.
    // (But it is no good practice!)
    int* data_send = (int*) frame.data;
    int* data_recv = (int*) frame_recv.data;
    for (int i = 0; i < frame.shape_y * frame.shape_x; i++) {
        assert(data_send[i] == data_recv[i]);
    }
}
