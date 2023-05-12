#include "Pub.h"
#include "Sub.h"

#include <string>
#include <cassert>
#include <iostream>
#include <unistd.h>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;


class TestPubSub {
public:
    TestPubSub();
    Sub sub;
    Pub pub;

    void test_send_recv();
    void test_send_recv_multipart();
    void test_send_recv_json();
};

TestPubSub::TestPubSub() {
    string host_pub = "*";
    int port = 5555;
    string topic = "topic";
    pub = Pub(host_pub, port, topic);

    string host_sub = "127.0.0.1";
    sub = Sub(host_sub, port, topic);

    // Sleep for 5 seconds so that the socket are properly set up and the
    // afterward send / recv calls work.
    cout << "Sleeping for 5 seconds." << endl;
    sleep(5.0);
}

void TestPubSub::test_send_recv() {
    cout << "Testing send - recv" << endl;
    size_t n_values = 10;
    int* data_int = new int[n_values];

    for (int i = 0; i < n_values; i++)
    {
        data_int[i] = i * i;
    }

    void* data = data_int;
    size_t size = sizeof(int) * n_values;

    pub.send(data, size);

    void* data_recv;
    size_t size_recv;

    sub.recv(data_recv, size_recv);
    int* data_recv_int = (int*) data_recv;

    for (int i = 0; i < n_values; i++) {
        assert(data_int[i] == data_recv_int[i]);
    }
}


void TestPubSub::test_send_recv_multipart() {
    cout << "Testing send_multipart - recv_multipart" << endl;
    size_t n_msgs = 2;
    vector<void*> datas (n_msgs);
    vector<size_t> sizes (n_msgs);

    string msg1 = "message1";
    datas[0] = (void*) msg1.c_str();
    sizes[0] = msg1.length();

    int msg2 = 100;
    datas[1] = (void*) &msg2;
    sizes[1] = sizeof(int);

    vector<void*> datas_recv;
    vector<size_t> sizes_recv;

    pub.send_multipart(datas, sizes);
    sub.recv_multipart(datas_recv, sizes_recv);

    string msg1_recv = string(static_cast<const char*> (datas_recv[0]), sizes_recv[0]);
    assert(msg1 == msg1_recv);

    int msg2_recv = *((int*) datas_recv[1]);
    assert(msg2 == msg2_recv);
}


void TestPubSub::test_send_recv_json() {
    cout << "Testing send_json - recv_json" << endl;
    Json::Value data;
    data["some_int"] = 512;
    data["some_string"] = 1.602 * 1e-16;

    pub.send_json(data);

    Json::Value data_recv = sub.recv_json();

    assert(data["some_int"] == data_recv["some_int"]);
    assert(data["some_string"] == data_recv["some_string"]);
}


int main() {
    TestPubSub test;

    test.test_send_recv();

    test.test_send_recv_multipart();

    test.test_send_recv_json();
}
