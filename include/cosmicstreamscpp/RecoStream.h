#pragma once

#include <zmq.hpp>
#include <string>
#include <json/json.h>
#include <cosmicstreamscpp/structs.h>

using std::string;

class Sub;
class Pub;

class RecoStream {
public:
    RecoStream() = default;
    RecoStream(const string& host_start,
               const string& host_frame,
               const string& host_stop,
               const string& host_abort,
               const bool& use_out);

    Sub* m_socket_start;
    string m_start_host;
    int m_start_port;
    string m_start_topic;

    Sub* m_socket_frame;
    string m_frame_host;
    int m_frame_port;
    string m_frame_topic;

    Sub* m_socket_stop;
    string m_stop_host;
    int m_stop_port;
    string m_stop_topic;

    Sub* m_socket_abort;
    string m_abort_host;
    int m_abort_port;
    string m_abort_topic;

    Pub* m_socket_rec;
    string m_rec_host;
    int m_rec_port;
    string m_rec_topic;
    bool m_use_out = true;

    void init_sockets();

    zmq::poller_t<> m_poller;
    zmq::poller_event<> get_event();

    bool something_in_queue();

    bool has_start_arrived();
    bool has_frame_arrived();
    bool has_stop_arrived();
    bool has_abort_arrived();

    Json::Value recv_start();
    Frame recv_frame();
    Json::Value recv_stop();
    Json::Value recv_abort();
    void send_rec(const Reco& reco);
};
