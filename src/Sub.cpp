#include "include/Sub.h"
#include "zmq_addon.hpp"

#include <iostream>

using std::to_string;
using std::cout;
using std::endl;


Sub::Sub(const string& host, const int& port, const string& topic)
{
    m_host = host;
    m_port = port;
    m_topic = topic;
    craft_address();

    m_socket = zmq::socket_t(m_context, zmq::socket_type::sub);
    cout << "Connecting to " << m_address << endl;
    m_socket.connect(m_address);
    cout << "Subscribing to topic: " << m_topic << endl;
    m_socket.set(zmq::sockopt::subscribe, m_topic);

    m_socket_ref = m_socket;
}

void Sub::recv(void*& data, size_t& size) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    string test = string(static_cast<const char*>(msgs[0].data()), msgs[0].size());
    string test2 = string(static_cast<const char*>(msgs[1].data()), msgs[1].size());

    // TODO: This implies that the receiver will deallocate the memory
    // Could there be a better solution so that the user is not responsible for the allocated memory?
    data = malloc(sizeof(char) * msgs[1].size());
    memcpy(data, msgs[1].data(), sizeof(char) * msgs[1].size());

    size = msgs[1].size();
}

void Sub::recv_multipart(vector<void*>& datas, vector<size_t>& sizes) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    datas = vector<void*> (msgs.size() - 1);
    sizes = vector<size_t> (msgs.size() - 1);

    for (int i = 0; i < datas.size(); i++)
    {
        sizes[i] = msgs[i + 1].size();
        datas[i] = malloc(sizeof(char) * msgs[i + 1].size());
        memcpy(datas[i], msgs[i + 1].data(), sizeof(char) * msgs[i + 1].size());
        // datas[i] = msgs[i + 1].data();
    }
}

Json::Value Sub::recv_json() {
    void* data;
    size_t size;

    recv(data, size);

    Json::Value metadata = highjson::loads(data, size);
    free(data);
    return metadata;
}

string Sub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
