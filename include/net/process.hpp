#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>

#include "../../include/msg_definition.hpp"

// void coutBytes(char data[64]);
void ini_all_devices();
void kill_all_devices();

int handleSystemRequest(const uint8_t* data);

int handleKeyboardRequest(const uint8_t* data);

int handleControllerRequest(const uint8_t* data);

int handleMouseRequest(const uint8_t* data);

#endif