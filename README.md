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

