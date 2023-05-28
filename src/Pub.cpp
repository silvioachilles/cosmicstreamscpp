#include "include/Pub.h"

#include <zmq_addon.hpp>
#include <iostream>
#include <array>
#include "include/highjson.h"
#include "structs.h"
#include "datatype_strings.h"

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

void Pub::send_frame(const Frame& frame) {
    Json::Value metadata;

    metadata["shape_y"] = frame.shape_y;
    metadata["shape_x"] = frame.shape_x;
    metadata["dtype"] = frame.dtype;
    metadata["byteorder"] = frame.byteorder;
    metadata["order"] = frame.order;
    metadata["identifier"] = frame.identifier;
    metadata["index"] = frame.index;
    metadata["posy"] = frame.posy;
    metadata["posx"] = frame.posx;

    void* data = (void*) frame.data;
    size_t dtype_size = datatype_size_from_string(frame.dtype);
    size_t size = frame.shape_y * frame.shape_x * dtype_size;

    vector<void*> datas (2);
    vector<size_t> sizes (2);

    string metadata_str = highjson::dumbs(metadata);
    datas[0] = (void*) metadata_str.c_str();
    sizes[0] = metadata_str.length();

    datas[1] = data;
    sizes[1] = size;

    send_multipart(datas, sizes);
}

void Pub::send_rec(const Reco& reco) {
    Json::Value metadata;

    metadata["shape_y"] = reco.shape_y;
    metadata["shape_x"] = reco.shape_x;
    metadata["dtype"] = reco.dtype;
    metadata["byteorder"] = reco.byteorder;
    metadata["order"] = reco.order;
    metadata["identifier"] = reco.identifier;
    metadata["obj_pixelsize_x"] = reco.pixelsize_x;
    metadata["obj_pixelsize_y"] = reco.pixelsize_y;

    void* data = (void*) reco.data;
    size_t dtype_size = datatype_size_from_string(reco.dtype);
    size_t size = reco.shape_y * reco.shape_x * dtype_size;

    vector<void*> datas (2);
    vector<size_t> sizes (2);

    string metadata_str = highjson::dumbs(metadata);
    datas[0] = (void*) metadata_str.c_str();
    sizes[0] = metadata_str.length();

    datas[1] = data;
    sizes[1] = size;

    send_multipart(datas, sizes);
}


string Pub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
