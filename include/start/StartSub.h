#pragma once

#include "Sub.h"
#include "../../globals/defaults.h"

#include <json/json.h>

using std::string;

class StartSub: Sub
{
public:
    StartSub(const string& host, const int& port = START_PORT, const string& topic = START_TOPIC);

    Json::Value recv_start();
};
