#include <iostream>
#include <string>

#include "FrameSub.h"

using std::string;
using std::cout;
using std::endl;


int main() {
    string host = "127.0.0.1";
    int port = 5555;
    string topic = "frame";
    FrameSub frame_sub (host, port, topic);

    while (true) {
        Frame frame = frame_sub.recv_frame();
        cout << "frame received" << endl;
        cout << "shape_y: " << frame.shape_y << endl;
        cout << "shape_x: " << frame.shape_x << endl;
        cout << "dtype: " << frame.dtype << endl;
    }
}
