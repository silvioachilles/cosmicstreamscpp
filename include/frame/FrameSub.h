#pragma once
#include "Sub.h"

#include <string>
#include <iostream>

#include <json/json.h>

using std::string;
using std::cout;
using std::endl;


struct Frame {
    size_t index;
    float posy;
    float posx;
    string identifier;

    string dtype;
    void* data;
    size_t shape_y;
    size_t shape_x;
    string byteorder;
    string order;

    Json::Value metadata;
};


class FrameSub: Sub {
public:
    FrameSub(string host, int port, string topic);

    Frame recv_frame();
};
