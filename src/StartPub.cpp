#include "StartPub.h"


StartPub::StartPub(const string& host, const int& port, const string& topic):
    Pub(host, port, topic) {

}

void StartPub::send_start(Json::Value metadata) {
    string metadata_str = highjson::dumbs(metadata);

    void* metadata_void_ptr = (void*) metadata_str.c_str();
    size_t metadata_size = metadata_str.length();

    send(metadata_void_ptr, metadata_size);
}
