#include "StartSub.h"
#include <json/json.h>

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;


int main()
{
    // This test intends that the metadata is received from somewhere else,
    // which was a Python script at the time of developing.

    string host = "127.0.0.1";
    int port = 5555;
    string topic = "start";
    StartSub start_sub (host, port, topic);
    while (true)
    {
        Json::Value metadata = start_sub.recv_start();

        float energy = metadata["energy"].asFloat();
        cout << "metadata received." << endl;
        cout << "Energy: " << to_string(energy) << endl;
        cout << "Distance: " << to_string(metadata["distance"].asFloat()) << endl;
        cout << "Pixel size: " << to_string(metadata["x_pixel_size"].asFloat()) << endl;
        cout << "Pixel count: " << to_string(metadata["output_pixel_count"].asFloat()) << endl;
    }
}
