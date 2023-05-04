#include "Pub.h"

#include <zmq_addon.hpp>
#include <iostream>
#include <array>

using std::to_string;
using std::cout;
using std::endl;
using std::array;


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
    zmq::message_t topic (m_topic);
    zmq::message_t msg (data, size);

    array<zmq::message_t, 2> msgs = {zmq::message_t(m_topic), zmq::message_t(data, size)};

    // m_socket.send(msg, zmq::send_flags::none);
    zmq::send_multipart(m_socket,msgs,zmq::send_flags::none);
}

string Pub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
