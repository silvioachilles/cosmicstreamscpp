#include "highjson.h"

#include <cassert>
#include <string>

using std::string;

int main() {
    string json_string = "{\"abc\":10,\"def\":[11,12]}\n";

    Json::Value json_value = highjson::loads(json_string);

    assert(json_value["abc"] == 10);
    assert(json_value["def"][0] == 11);
    assert(json_value["def"][1] == 12);

    string json_string_reloaded = highjson::dumbs(json_value);
    assert(json_string_reloaded == json_string);

    void* data = (void*) json_string.c_str();
    size_t size = json_string.length();
    Json::Value json_value_reloaded = highjson::loads(data, size);

    assert(json_value["abc"] == json_value_reloaded["abc"]);
    assert(json_value["def"][0] == json_value_reloaded["def"][0]);
    assert(json_value["def"][1] == json_value_reloaded["def"][1]);
}
