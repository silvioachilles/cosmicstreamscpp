#pragma once
#include "Sub.h"

#include <string>
#include <iostream>

#include <json/json.h>

using std::string;
using std::cout;
using std::endl;


struct frame {
    int index;
    float pos_y;
    float pos_x;
    string identifier;

    string dtype;
    void* data;
    size_t data_ny;
    size_t data_nx;
    string byteorder;
    string elemorder;

    Json::Value metadata;
};


class FrameSub: Sub {
public:
    FrameSub(string host, int port, string topic);

    frame recv_frame();
};
