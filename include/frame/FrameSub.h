#pragma once
#include "Sub.h"
#include "structs.h"

#include <string>
#include <iostream>

#include <json/json.h>

using std::string;
using std::cout;
using std::endl;


class FrameSub: public Sub {
public:
    FrameSub() = default;
    FrameSub(string host, int port, string topic);

    Frame recv_frame();
};
