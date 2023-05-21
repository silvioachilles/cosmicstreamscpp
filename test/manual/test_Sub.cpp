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

    Sub sub (host, port, topic);

    void* data;
    size_t size;

    while (true)
    {
        cout << "Waiting to receive data." << endl;
        sub.recv(data, size);
        cout << "Message received" << endl;

        size_t n_values = size / sizeof(float);
        float* data_float = (float*) data;

        cout << "Received values are: ";
        for (int i = 0; i < n_values; i++) {
            float value = data_float[i];
            cout << to_string(value) << " ";
        }
        cout << endl;
    }
}
