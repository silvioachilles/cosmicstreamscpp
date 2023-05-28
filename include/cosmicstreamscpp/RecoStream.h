#include "cosmicstreamscpp/Sub.h"
#include "cosmicstreamscpp/Pub.h"
#include "cosmicstreamscpp/defaults.h"

#include <string>

using std::string;

class RecoStream {
public:
    Sub m_socket_start;
    string m_start_host;
    int m_start_port = START_PORT;
    string m_start_topic = START_TOPIC;

    Sub m_socket_frame;
    string m_frame_host;
    int m_frame_port = FRAME_PORT;
    string m_frame_topic = FRAME_TOPIC;

    Sub m_socket_stop;
    string m_stop_host;
    int m_stop_port = STOP_PORT;
    string m_stop_topic = STOP_TOPIC;

    Sub m_socket_abort;
    string m_abort_host;
    int m_abort_port = ABORT_PORT;
    string m_abort_topic = ABORT_TOPIC;

    Pub m_socket_rec;
    string m_rec_host = PUB_HOST_ALL;
    int m_rec_port = REC_PORT;
    string m_rec_topic = REC_TOPIC;
    bool m_use_out = true;

    zmq::poller_t<> m_poller;

    RecoStream() = default;
    RecoStream(const string& host_start,
               const string& host_frame,
               const string& host_stop,
               const string& host_abort,
               const bool& use_out);

    void init_sockets();

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
