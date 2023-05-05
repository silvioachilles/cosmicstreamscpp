#include "FrameSub.h"

#include <vector>

using std::vector;


FrameSub::FrameSub(string host, int port, string topic):
    Sub(host, port, topic) {

}

frame FrameSub::recv_frame() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    string metadata = string(static_cast<const char *>(datas[1]), sizes[1]);
    Json::Reader reader;



}