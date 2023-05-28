#pragma once

#include <string>
#include <json/json.h>

using std::string;


struct Image {
    string dtype;
    void* data;
    size_t shape_y;
    size_t shape_x;
    string byteorder;
    string order;

    Json::Value metadata;
};


struct Frame: Image {
    string identifier;
    size_t index;
    float posy;
    float posx;
};


struct Reco: Image {
    string identifier;
    float pixelsize_x;
    float pixelsize_y;
};
