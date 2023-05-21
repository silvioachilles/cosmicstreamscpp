#include "include/Pub.h"
#include "TestData.h"

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

    Pub start_pub = Pub(host, port, topic);

    Json::Value metadata = get_startdata();

    while (true) {
        cout << "Enter something to start sending metadata." << endl;
        string input;
        cin >> input;

        start_pub.send_json(metadata);
        cout << "Metadata sent." << endl;
    }
}
