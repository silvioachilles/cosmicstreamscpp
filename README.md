cosmicstreamscpp

The pre-decisions for the creation of this repository are captured here:
https://docs.google.com/document/d/1ZfKQh1YZ1TV16pfNNddB979664ZL49z5ZQM5TNRJBRY/edit


**Installation**

It is required to have
1. jsoncpp
2. cppzmq

installed and findable via cmake find_package.  Then,

```
mkdir build
cmake .. -DCMAKE_INSTALL_PREFIX=<path to install>
make
make install
```

If cmake fails to find one of the required libraries you can specify custom locations 
```
cmake .. -Djsoncpp_DIR=~/somefolder/share/jsoncpp  -Dcppzmq_DIR=~/somefolder/share/cmake/cppzmq
```



**Usage**

The headers are located in
```
${CMAKE_INSTALL_PREFIX}/include/cosmicstreamscpp
```
The library is located at 
```
${CMAKE_INSTALL_PREFIX}/lib/libcosmicstreamscpp.a
```
CMake support is given at
```
${CMAKE_INSTALL_PREFIX}/share/cmake/cosmicstreamscpp
```
so in case of using cmake, you may want to point cmake to the right directory: 
```
cmake .. -DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}
```
Be aware that using libcosmicstreamscpp.a still requires to link cppzmq and jsoncpp to your project.


**Example**
```c++

#include "RecoStream.h"
#include <complex>
#include <string>
using std::string;
using std::complex;

int main() {
    string host_start = "127.0.0.1";
    string host_frame = "127.0.0.1";
    string host_stop = "127.0.0.1";
    string host_abort = "127.0.0.1";
    bool stream_reco_out = true;
    RecoStream streamer (host_start, host_frame, host_stop, host_abort, stream_reco_out);

    // Advanced settings. The values shown below are the default values.
    streamer.m_start_port = 37013;
    streamer.m_start_topic = "start";

    streamer.m_frame_port = 37013;
    streamer.m_frame_topic = "frame";

    streamer.m_stop_port = 37013;
    streamer.m_stop_topic = "stop";

    streamer.m_abort_port = 37013;
    streamer.m_abort_topic = "abort";

    streamer.m_rec_port = 37016;
    streamer.m_rec_topic = "rec";

    streamer.init_sockets();

    // Query input sockets
    if (streamer.something_in_queue()) {
        if (streamer.has_start_arrived()) {
            Json::Value start_metadata = streamer.recv_start();
        }
        if (streamer.has_frame_arrived()) {
            Frame frame = streamer.recv_frame();

            int ny = frame.shape_y;
            int nx = frame.shape_x;
            string dtype = frame.dtype;
            string identifier = frame.identifier;
            int index = frame.index;
            float posx = frame.posx;
            float posy = frame.posy;
            void* data = frame.data;
            Json::Value metadata = frame.metadata;
        }
        if (streamer.has_stop_arrived()) {
            Json::Value stop_metadata = streamer.recv_stop();
        }
        if (streamer.has_abort_arrived()) {
            Json::Value abort_metadata = streamer.recv_abort();
        }
    }

    // Output
    Reco reco;
    reco.shape_y = 10;
    reco.shape_x = 10;
    reco.pixelsize_y = 10.0 * 1e-9;
    reco.pixelsize_y = 10.0 * 1e-9;
    reco.dtype = "complex64";
    reco.identifier = "dataset001";
    reco.order = "C";
    reco.byteorder = "<";
    
    auto* data = new complex<float>[reco.shape_y * reco.shape_x];
    for (int iy = 0; iy < reco.shape_y; iy++) {
        for (int ix = 0; ix < reco.shape_x; ix++) {
            data[iy * reco.shape_x + ix] = complex<float>(0.1f * iy, 0.1f * ix);
        }
    }
    
    reco.data = (void*) data;
    streamer.send_rec(reco);
    delete[] data;
}
```
