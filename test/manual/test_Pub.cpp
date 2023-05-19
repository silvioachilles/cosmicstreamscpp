#include "Pub.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;


int main()
{
    cout << "Starting test_pub" << endl;

    string host = "*";
    int port = 5555;
    string topic;

    Pub pub(host, port, topic);

    size_t n_values = 10;
    float* data_float = new float[n_values];

    for (int i = 0; i < n_values; i++)
    {
        data_float[i] = i * i;
    }

    void* data = data_float;
    size_t size = sizeof(float) * n_values;

    while (true) {
        cout << "Enter something to send a message." << endl;
        string input;
        cin >> input;
        pub.send(data, size);
    }
}