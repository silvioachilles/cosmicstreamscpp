#pragma once
#include "Sub.h"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class FrameSub: Sub {
    FrameSub(string host, int port, string topic);

    void recv_frame();
};
