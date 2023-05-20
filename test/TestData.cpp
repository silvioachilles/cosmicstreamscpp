#include "TestData.h"


Json::Value get_startdata() {
    Json::Value translations(Json::arrayValue);
    float xmin = 0;
    float ymin = 0;
    float xmax = 4 * 1e-6;
    float ymax = 4 * 1e-6;
    float dx = 4 * 1e-7;
    float dy = 4 * 1e-7;
    int nx = (xmax - xmin) / dx;
    int ny = (ymax - ymin) / dy;

    for (int iy = 0; iy < ny; iy++) {
        for (int ix = 0; ix < nx; ix++) {
            Json::Value translation (Json::arrayValue);
            float y = ymin + iy * dy;
            float x = xmin + ix * dx;
            translation.append(x);
            translation.append(y);
            translations.append(translation);
        }
    }

    Json::Value metadata;
    metadata["distance"] = 0.121;
    metadata["output_pixel_count"] = 512;
    metadata["energy"] = 1.602 * 1e-16;
    metadata["translations"] = translations;

    return metadata;
}

Frame get_framedata() {
    size_t ny = 10;
    size_t nx = 10;
    string dtype = "int32";

    int* data = new int[ny * nx];
    for (int i = 0; i < ny * nx; i++) {
        data[i] = i;
    }

    Frame frame;
    frame.identifier = "id";
    frame.index = 100;
    frame.posx = 10.0;
    frame.posy = 10.0;
    frame.shape_y = ny;
    frame.shape_x = nx;
    frame.dtype = dtype;
    frame.byteorder = "<";
    frame.order = "C";
    frame.data = (void*) data;

    return frame;
}

Json::Value get_stopdata() {
    Json::Value metadata;
    metadata["something"] = "something";

    return metadata;
}

Json::Value get_abortdata() {
    Json::Value metadata;
    metadata["something"] = "something";

    return metadata;
}
