#include "FramePub.h"
#include "FrameSub.h"

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
    FramePub frame_pub (host_pub, port, topic);

    string host_sub = "127.0.0.1";

    cout << "Setting up FrameSub" << endl;
    FrameSub frame_sub (host_sub, port, topic);

    cout << "Sleeping for 5 seconds to allow sockets to initialize" << endl;
    sleep(5.0);

    size_t ny = 10;
    size_t nx = 10;
    string dtype = "int32";

    int* data = new int[ny * nx];
    for (int i = 0; i < ny * nx; i++) {
        data[i] = i;
    }

    Frame frame;
    frame.identifier = "id";
    frame.index = 100;
    frame.posx = 10.0;
    frame.posy = 10.0;
    frame.shape_y = ny;
    frame.shape_x = nx;
    frame.dtype = dtype;
    frame.byteorder = "<";
    frame.order = "C";
    frame.data = (void*) data;

    frame_pub.send_frame(frame);

    Frame frame_recv = frame_sub.recv_frame();

    assert(frame.identifier == frame_recv.identifier);
    assert(frame.index == frame_recv.index);
    assert(frame.posx == frame_recv.posx);
    assert(frame.posy == frame_recv.posy);
    assert(frame.shape_y == frame_recv.shape_y);
    assert(frame.shape_x == frame_recv.shape_x);
    assert(frame.dtype == frame_recv.dtype);
    assert(frame.byteorder == frame_recv.byteorder);
    assert(frame.order == frame_recv.order);

    int* data_recv = (int*) frame_recv.data;
    for (int i = 0; i < ny * nx; i++) {
        assert(data[i] == data_recv[i]);
    }
}
