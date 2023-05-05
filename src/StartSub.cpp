#include "StartSub.h"
#include "highjson.h"

using std::unique_ptr;

StartSub::StartSub(const string& host, const int& port, const string& topic):
    Sub(host, port, topic)
{

}

Json::Value StartSub::recv_start() {
    vector<void*> datas;
    vector<size_t> sizes;

    recv_multipart(datas, sizes);

    void* metadata_void = datas[1];
    size_t size = sizes[1];

    Json::Value metadata = highjson::loads(metadata_void, size);
    return metadata;
}
