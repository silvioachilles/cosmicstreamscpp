#include "StartSub.h"

using std::unique_ptr;

StartSub::StartSub(const string& host, const int& port, const string& topic):
    Sub(host, port, topic)
{

}

Json::Value StartSub::recv_start() {
    void* data;
    size_t size;

    recv(data, size);
    string* data_topic_string_ptr = static_cast<string*>(data);
//    string data_topic_string = *data_topic_string_ptr;
    string data_string = data_topic_string_ptr->substr(5);
    int data_length = static_cast<int>(data_string.length());

    Json::CharReaderBuilder builder;
    const unique_ptr<Json::CharReader> reader(builder.newCharReader());

    Json::Value metadata;
    JSONCPP_STRING err;

    bool read_success = reader->parse(
            data_string.c_str(),
            data_string.c_str() + data_length,
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
