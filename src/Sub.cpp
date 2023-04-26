#include "Sub.h"

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

string Sub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
