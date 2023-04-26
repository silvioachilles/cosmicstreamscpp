#pragma once

#include <string>
#include <zmq.hpp>


using std::string;

class Pub
{
public:
    Pub() = default;
    Pub(const string& host, const int& port, const string& topic);

    string m_host;
    int m_port;
    string m_topic;
    string m_address;

    zmq::context_t m_context;
    zmq::socket_t m_socket;

    void send(void* data, size_t size);

    string craft_address();
};
