#include "include/Sub.h"

#include <iostream>
#include <string>

using std::string;
using std::endl;
using std::cout;
using std::to_string;


int main() {
    cout << "Starting test_sub" << endl;

    string host = "127.0.0.1";
    int port = 5555;
    string topic;

    // Here, it is only tested if the constructor of the Sub class succeeds.
    // The recv calls of the Sub class are all blocking. A test would hence rely
    // on an active publisher somewhere. This case will be tested in test_PubSub.cpp.
    Sub sub (host, port, topic);
}

