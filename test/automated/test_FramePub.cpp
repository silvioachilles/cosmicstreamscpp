#include "FramePub.h"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


int main() {
    string host = "*";
    int port = 5555;
    string topic = "frame";

    FramePub frame_pub (host, port, topic);

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
}
