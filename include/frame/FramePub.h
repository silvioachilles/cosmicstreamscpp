#pragma once

#include "Pub.h"
#include "structs.h"
#include <string>

using std::string;

class FramePub: Pub {
public:
    FramePub() = default;
    FramePub(const string& host, const int& port, const string& topic);

    void send_frame(const Frame& frame);
};
