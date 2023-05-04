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
    // Update: this test also works in combination with test_StartPub

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

        cout << "Translations:" << endl;
        Json::Value translations = metadata["translations"];
        for (Json::Value::const_iterator it=translations.begin(); it != translations.end(); ++it)
        {
            Json::Value::ArrayIndex ix = 0;
            Json::Value x = it->get(ix, 0);
            Json::Value::ArrayIndex iy = 1;
            Json::Value y = it->get(iy, 0);

            cout << "x: " << x << "\ty: " << y << endl;
        }
    }
}
