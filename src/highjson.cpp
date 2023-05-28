#include "include/cosmicstreamscpp/highjson.h"


using std::unique_ptr;

Json::Value highjson::loads(void* data, size_t size) {
    string json_string = string(static_cast<const char*>(data), size);

    Json::Value json_value = highjson::loads(json_string);

    return json_value;
}

Json::Value highjson::loads(const string& json_string) {
    Json::CharReaderBuilder builder;
    const unique_ptr<Json::CharReader> reader(builder.newCharReader());

    Json::Value metadata;
    JSONCPP_STRING err;

    bool read_success = reader->parse(
            json_string.c_str(),
            json_string.c_str() + json_string.length(),
            &metadata,
            &err
    );

    if (read_success)
    {
        return metadata;
    }
    else
    {
        throw std::logic_error("Could not parse string to Json::Value.");
    }
}

string highjson::dumbs(Json::Value json_value) {
    Json::FastWriter writer;
    string json_string = writer.write(json_value);

    return json_string;
}
