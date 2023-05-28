#include "cosmicstreamscpp/RecoStream.h"
#include <string>
#include <iostream>
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::cin;


int main() {
    string host = "127.0.0.1";
    int port = 5555;
    RecoStream streamer (host, host, host, host, true);
    streamer.m_start_port = port;
    streamer.m_frame_port = port;
    streamer.m_stop_port = port;
    streamer.m_abort_port = port;
    streamer.init_sockets();

    while (true) {
        if (streamer.something_in_queue())
        {
            if (streamer.has_start_arrived()) {
                Json::Value start_metadata = streamer.recv_start();
                cout << "Received start" << endl;
            }
            if (streamer.has_frame_arrived()) {
                Frame frame = streamer.recv_frame();
                cout << "Received frame" << endl;
            }
            if (streamer.has_stop_arrived()) {
                Json::Value stop_metadata = streamer.recv_stop();
                cout << "Received stop" << endl;
            }
            if (streamer.has_abort_arrived()) {
                Json::Value abort_metadata = streamer.recv_abort();
                cout << "Received abort" << endl;
            }
        }
    }
}
