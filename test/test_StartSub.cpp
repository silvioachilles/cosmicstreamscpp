#include "StartSub.h"
#include <json/json.h>

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


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

        cout << "metadata received." << endl;
    }
}
