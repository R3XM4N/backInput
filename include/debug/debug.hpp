#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../net/instructions/msg_definition.hpp"

#define LOG_LOCATION_TEMP   "temp.log"
#define LOG_LOCATION_SAVED  "latest.log"

void loggingStart();
void logRecieved(char data[SOCKET_SIZE_WHOLE]);
void logStop();
void logCharPtr(char* data);

#endif