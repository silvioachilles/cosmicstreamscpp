#include <iostream>
#include <string>

#include "cosmicstreamscpp/Sub.h"

using std::string;
using std::cout;
using std::endl;


int main() {
    string host = "127.0.0.1";
    int port = 5555;
    string topic = "frame";
    Sub frame_sub (host, port, topic);

    // The subscription relies on an active Publisher, so this first test
    // only covers if the constructor succeeds.
}
