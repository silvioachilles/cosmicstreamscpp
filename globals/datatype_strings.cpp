#include "datatype_strings.h"
#include <typeinfo>
#include <stdexcept>

using std::logic_error;

size_t datatype_size_from_string(const string& dtype_str) {
    size_t return_value;
    if (dtype_str == "float32") {
        return_value = 4;
    }
    else if (dtype_str == "float64") {
        return_value = 8;
    }
    else if (dtype_str == "int32") {
        return_value = 4;
    }
    else if (dtype_str == "int64") {
        return_value = 8;
    }
    else {
        throw logic_error("dtype_str '" + dtype_str + "' not known.");
    }
    return return_value;
}
