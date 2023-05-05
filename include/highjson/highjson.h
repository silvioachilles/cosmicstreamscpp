#pragma once

#include <string>

#include <json/json.h>

using std::string;

namespace highjson {
    Json::Value loads(void* data, size_t size);

    Json::Value loads(const string& json_string);

    string dumbs(Json::Value json_value);
}
