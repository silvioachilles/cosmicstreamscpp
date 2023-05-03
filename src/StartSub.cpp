#include "StartSub.h"

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

    string metadata_str = string(static_cast<const char*>(metadata_void), size);

    Json::CharReaderBuilder builder;
    const unique_ptr<Json::CharReader> reader(builder.newCharReader());

    Json::Value metadata;
    JSONCPP_STRING err;

    bool read_success = reader->parse(
            metadata_str.c_str(),
            metadata_str.c_str() + metadata_str.length(),
            &metadata,
            &err
            );

    if (read_success)
    {
        return metadata;
    }
    else
    {
        throw std::logic_error("Could not parse received metadata.");
    }
}
