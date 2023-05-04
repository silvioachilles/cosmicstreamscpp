#include "StartPub.h"


StartPub::StartPub(const string& host, const int& port, const string& topic):
    Pub(host, port, topic) {

}

void StartPub::send_start(Json::Value metadata) {
    Json::FastWriter writer;
    string metadata_str = writer.write(metadata);
    const char* metadata_char_ptr = metadata_str.c_str();
    void* metadata_void_ptr = (void*) metadata_char_ptr;
    size_t metadata_size = metadata_str.length();

    send(metadata_void_ptr, metadata_size);
}