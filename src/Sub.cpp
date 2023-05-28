#include "include/Sub.h"
#include "zmq_addon.hpp"

#include <iostream>

using std::to_string;
using std::cout;
using std::endl;


Sub::Sub(const string& host, const int& port, const string& topic)
{
    m_host = host;
    m_port = port;
    m_topic = topic;
    craft_address();

    m_socket = zmq::socket_t(m_context, zmq::socket_type::sub);
    cout << "Connecting to " << m_address << endl;
    m_socket.connect(m_address);
    cout << "Subscribing to topic: " << m_topic << endl;
    m_socket.set(zmq::sockopt::subscribe, m_topic);

    m_socket_ref = m_socket;
}

void Sub::recv(void*& data, size_t& size) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    string test = string(static_cast<const char*>(msgs[0].data()), msgs[0].size());
    string test2 = string(static_cast<const char*>(msgs[1].data()), msgs[1].size());

    // TODO: This implies that the receiver will deallocate the memory
    // Could there be a better solution so that the user is not responsible for the allocated memory?
    data = malloc(sizeof(char) * msgs[1].size());
    memcpy(data, msgs[1].data(), sizeof(char) * msgs[1].size());

    size = msgs[1].size();
}

void Sub::recv_multipart(vector<void*>& datas, vector<size_t>& sizes) {
    vector<zmq::message_t> msgs;

    zmq::recv_multipart(m_socket, std::back_inserter(msgs));

    datas = vector<void*> (msgs.size() - 1);
    sizes = vector<size_t> (msgs.size() - 1);

    for (int i = 0; i < datas.size(); i++)
    {
        sizes[i] = msgs[i + 1].size();
        datas[i] = malloc(sizeof(char) * msgs[i + 1].size());
        memcpy(datas[i], msgs[i + 1].data(), sizeof(char) * msgs[i + 1].size());
        // datas[i] = msgs[i + 1].data();
    }
}

Json::Value Sub::recv_json() {
    void* data;
    size_t size;

    recv(data, size);

    Json::Value metadata = highjson::loads(data, size);
    free(data);
    return metadata;
}

Frame Sub::recv_frame() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    Json::Value metadata = highjson::loads(datas[0], sizes[0]);
    free(datas[0]);

    Frame frame;

    frame.shape_y = metadata["shape_y"].asInt();
    frame.shape_x = metadata["shape_x"].asInt();
    frame.dtype = metadata["dtype"].asString();
    frame.byteorder = metadata["byteorder"].asString();
    frame.order = metadata["order"].asString();
    frame.identifier = metadata["identifier"].asString();
    frame.index = metadata["index"].asInt();
    frame.posy = metadata["posy"].asFloat();
    frame.posx = metadata["posx"].asFloat();
    frame.data = datas[1];
    frame.metadata = metadata;

    return frame;
}

Reco Sub::recv_rec() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    Json::Value metadata = highjson::loads(datas[0], sizes[0]);
    free(datas[0]);

    Reco reco;

    reco.shape_y = metadata["shape_y"].asInt();
    reco.shape_x = metadata["shape_x"].asInt();
    reco.dtype = metadata["dtype"].asString();
    reco.byteorder = metadata["byteorder"].asString();
    reco.order = metadata["order"].asString();
    reco.identifier = metadata["identifier"].asString();
    reco.pixelsize_x = metadata["obj_pixelsize_x"].asFloat();
    reco.pixelsize_y = metadata["obj_pixelsize_y"].asFloat();
    reco.data = datas[1];
    reco.metadata = metadata;

    return reco;
}

string Sub::craft_address() {
    m_address = "tcp://" + m_host + ":" + to_string(m_port);
    return m_address;
}
