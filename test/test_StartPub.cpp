#include "StartPub.h"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;


int main()
{
    string host = "*";
    int port = 5555;
    string topic = "start";

    StartPub start_pub = StartPub(host, port, topic);

    // Create the metadata that is send afterwards.
    // translations first.
    Json::Value translations(Json::arrayValue);
    float xmin = 0;
    float ymin = 0;
    float xmax = 4 * 1e-6;
    float ymax = 4 * 1e-6;
    float dx = 4 * 1e-7;
    float dy = 4 * 1e-7;
    int nx = (xmax - xmin) / dx;
    int ny = (ymax - ymin) / dy;

    for (int iy = 0; iy < ny; iy++) {
        for (int ix = 0; ix < nx; ix++) {
            Json::Value translation (Json::arrayValue);
            float y = ymin + iy * dy;
            float x = xmin + ix * dx;
            translation.append(x);
            translation.append(y);
            translations.append(translation);
        }
    }


    Json::Value metadata;
    metadata["distance"] = 0.121;
    metadata["output_pixel_count"] = 512;
    metadata["energy"] = 1.602 * 1e-16;
    metadata["translations"] = translations;

    while (true) {
        cout << "Enter something to start sending metadata." << endl;
        string input;
        cin >> input;

        start_pub.send_start(metadata);
        cout << "Metadata sent." << endl;
    }
}
