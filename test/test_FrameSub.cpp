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


    cout << "Works" << endl;
}
