#include "Pub.h"

#include <zmq_addon.hpp>
#include <iostream>
#include <array>
#include "highjson.h"

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
}

void Pub::send(void* data, const size_t size) {
    zmq::message_t topic (m_topic);
    zmq::message_t msg (data, size);

    array<zmq::message_t, 2> msgs = {zmq::message_t(m_topic), zmq::message_t(data, size)};

    zmq::send_multipart(m_socket,msgs,zmq::send_flags::none);
}

void Pub::send_multipart(const vector<void*>& datas, const vector<size_t>& sizes) {
    // array<zmq::message_t, datas.size()> msgs;
    vector<zmq::message_t> msgs (datas.size() + 1);
    msgs[0] = zmq::message_t(m_topic);

    for (int i = 0; i < datas.size(); i++) {
        msgs[i + 1] = zmq::message_t(datas[i], sizes[i]);
    }

    zmq::send_multipart(m_socket, msgs, zmq::send_flags::none);
}

void Pub::send_json(const Json::Value& json_value) {
    string metadata_str = highjson::dumbs(json_value);

    void* metadata_void_ptr = (void*) metadata_str.c_str();
    size_t metadata_size = metadata_str.length();

    send(metadata_void_ptr, metadata_size);
}

string Pub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
