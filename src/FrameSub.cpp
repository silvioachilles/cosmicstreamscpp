#include "FrameSub.h"

#include <vector>
#include "highjson.h"

using std::vector;


FrameSub::FrameSub(string host, int port, string topic):
    Sub(host, port, topic) {

}

Frame FrameSub::recv_frame() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    Json::Value metadata = highjson::loads(datas[0], sizes[0]);

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
