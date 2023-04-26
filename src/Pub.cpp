#include "Pub.h"

#include <iostream>

using std::to_string;
using std::cout;
using std::endl;


Pub::Pub(const string& host, const int& port, const string& topic) {
    m_host = host;
    m_port = port;
    m_topic = topic;

    m_socket = zmq::socket_t(m_context, zmq::socket_type::pub);

    craft_address();
    cout << "Binding to " << m_address << endl;
    m_socket.bind(m_address);

    return;
}

void Pub::send(void* data, const size_t size) {
    zmq::message_t msg (data, size);
    m_socket.send(msg, zmq::send_flags::none);
}

string Pub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
