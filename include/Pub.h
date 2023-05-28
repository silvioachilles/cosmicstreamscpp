#pragma once

#include <string>
#include <zmq.hpp>
#include <json/json.h>
#include <vector>
#include "structs.h"

using std::vector;


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
    void send_multipart(const vector<void*>& datas, const vector<size_t>& sizes);
    void send_json(const Json::Value& json_value);
    void send_frame(const Frame& frame);
    void send_rec(const Reco& reco);

    string craft_address();
};
