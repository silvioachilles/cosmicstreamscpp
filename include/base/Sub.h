#pragma once

#include <string>
#include <zmq.hpp>
#include <vector>

using std::vector;
using std::string;

class Sub
{
public:
    Sub() = default;
    Sub(const string& host, const int& port, const string& topic);

    zmq::context_t m_context;
    zmq::socket_t m_socket;

    string m_host;
    int m_port;
    string m_topic;
    string m_address;

    void recv(void*& data, size_t& size);
    void recv_multipart(vector<void*>& datas, vector<size_t>& sizes);

    string craft_address();
};