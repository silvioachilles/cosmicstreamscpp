#pragma once

#include "Pub.h"
#include "defaults.h"
#include <string>
#include <json/json.h>

using std::string;

class StartPub: Pub
{
public:
    explicit StartPub(const string& host = PUB_HOST_ALL, const int& port = START_PORT, const string& topic = START_TOPIC);

    void send_start(Json::Value metadata);
};