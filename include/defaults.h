#pragma once

#include <string>

using std::string;

int FRAME_PORT = 37013;
string FRAME_TOPIC = b'frame';

int REC_PORT = 37016;
string REC_TOPIC = b'rec';

int START_PORT = 37013;
string START_TOPIC = b'start';

int STOP_PORT = 37013;
string STOP_TOPIC = b'stop';

int ABORT_PORT = 37013;
string ABORT_TOPIC = b'abort';
