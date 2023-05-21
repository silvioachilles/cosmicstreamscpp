#pragma once

#include <string>
#include <zmq.hpp>
#include <vector>
#include "highjson.h"

using std::vector;
using std::string;

class Sub
{
public:
    Sub() = default;
    Sub(const string& host, const int& port, const string& topic);

    zmq::context_t m_context;
    zmq::socket_t m_socket;
    zmq::socket_ref m_socket_ref;

    string m_host;
    int m_port;
    string m_topic;
    string m_address;

    void recv(void*& data, size_t& size);
    void recv_multipart(vector<void*>& datas, vector<size_t>& sizes);
    Json::Value recv_json();

    string craft_address();
};