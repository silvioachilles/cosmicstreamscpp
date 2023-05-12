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

    m_socket_ref = m_socket;
}

void Sub::recv(void*& data, size_t& size) {
    zmq::recv_result_t result_topic;
    zmq::message_t msg_topic;
    zmq::recv_result_t result_data;
    zmq::message_t msg_data;

    result_topic = m_socket.recv(msg_topic, zmq::recv_flags::none);
    result_data = m_socket.recv(msg_data, zmq::recv_flags::none);

    data = msg_data.data();
    size = msg_data.size();
}

void Sub::recv_multipart(vector<void*>& datas, vector<size_t>& sizes) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    datas = vector<void*> (msgs.size() - 1);
    sizes = vector<size_t> (msgs.size() - 1);

    for (int i = 0; i < datas.size(); i++)
    {
        datas[i] = msgs[i + 1].data();
        sizes[i] = msgs[i + 1].size();
    }
}

Json::Value Sub::recv_json() {
    void* metadata_void;
    size_t size;

    recv(metadata_void, size);

    Json::Value metadata = highjson::loads(metadata_void, size);
    return metadata;
}

string Sub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
