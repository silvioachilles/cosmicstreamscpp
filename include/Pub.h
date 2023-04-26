#pragma once

#include <string>
#include <zmq.hpp>


using std::string;

class Pub
{
public:
    Pub(string host, int port, string topic);

    string m_host;
    int m_port;
    string m_topic;

    zmq::context_t m_context;
    zmq::socket_t m_socket;

    void send();
};
