#include "Sub.h"
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
}

void Sub::recv(void*& data, size_t& size) {
    zmq::recv_result_t result;
    zmq::message_t msg;

    result = m_socket.recv(msg, zmq::recv_flags::none);

    data = msg.data();
    size = msg.size();
}

void Sub::recv_multipart(vector<void*>& datas, vector<size_t>& sizes) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    datas = vector<void*> (msgs.size());
    sizes = vector<size_t> (msgs.size());

    for (int i = 0; i < msgs.size(); i++)
    {
        datas[i] = msgs[i].data();
        sizes[i] = msgs[i].size();
    }
}

Json::Value Sub::recv_json() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    void* metadata_void = datas[1];
    size_t size = sizes[1];

    Json::Value metadata = highjson::loads(metadata_void, size);
    return metadata;
}

string Sub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
