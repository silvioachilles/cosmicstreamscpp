#include "FramePub.h"

#include "highjson.h"

#include "datatype_strings.h"

FramePub::FramePub(const string& host, const int& port, const string& topic):
    Pub(host, port, topic) {
}

void FramePub::send_frame(const Frame& frame) {
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
}
