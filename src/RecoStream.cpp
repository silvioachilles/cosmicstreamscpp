#include "include/RecoStream.h"

#include <vector>
#include <chrono>

using std::vector;


RecoStream::RecoStream(const string& host_start,
                       const string& host_frame,
                       const string& host_stop,
                       const string& host_abort) {
    m_start_host = host_start;
    m_frame_host = host_frame;
    m_stop_host = host_stop;
    m_abort_host = host_abort;
}

void RecoStream::init_sockets() {
    m_socket_start = Sub(m_start_host, m_start_port, m_start_topic);
    m_socket_frame = FrameSub(m_frame_host, m_frame_port, m_frame_topic);
    m_socket_stop = Sub(m_stop_host, m_stop_port, m_stop_topic);
    m_socket_abort = Sub(m_abort_host, m_abort_port, m_abort_topic);

    m_poller = zmq::poller_t<> ();
    m_poller.add(m_socket_start.m_socket_ref, zmq::event_flags::pollin);
    m_poller.add(m_socket_frame.m_socket_ref, zmq::event_flags::pollin);
    m_poller.add(m_socket_stop.m_socket_ref, zmq::event_flags::pollin);
    m_poller.add(m_socket_abort.m_socket_ref, zmq::event_flags::pollin);
}

zmq::poller_event<> RecoStream::get_event() {
    vector<zmq::poller_event<>> events (1);
    std::chrono::milliseconds timeout(0);
    m_poller.wait_all(events, timeout);

    return events[0];
}

bool RecoStream::something_in_queue() {
    zmq::poller_event<> event = get_event();

    if (event.socket.handle() == NULL) {
        return false;
    }
    return true;
}

bool RecoStream::has_start_arrived() {
    zmq::poller_event<> event = get_event();

    if (event.socket.handle() == m_socket_start.m_socket.handle()) {
        return true;
    }

    return false;
}

bool RecoStream::has_frame_arrived() {
    zmq::poller_event<> event = get_event();

    if (event.socket.handle() == m_socket_frame.m_socket.handle()) {
        return true;
    }

    return false;
}

bool RecoStream::has_stop_arrived() {
    zmq::poller_event<> event = get_event();

    if (event.socket.handle() == m_socket_stop.m_socket.handle()) {
        return true;
    }

    return false;
}

bool RecoStream::has_abort_arrived() {
    zmq::poller_event<> event = get_event();

    if (event.socket.handle() == m_socket_abort.m_socket.handle()) {
        return true;
    }

    return false;
}

Json::Value RecoStream::recv_start() {
    return m_socket_start.recv_json();
}

Frame RecoStream::recv_frame() {
    return m_socket_frame.recv_frame();
}

Json::Value RecoStream::recv_stop() {
    return m_socket_stop.recv_json();
}

Json::Value RecoStream::recv_abort() {
    return m_socket_abort.recv_json();
}
