#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "../../include/msg_definition.hpp"

void coutBytes(char data[64]);
void ini_all_devices();
void kill_all_devices();

int handleSystemRequest(char data[64]);

int handleKeyboardRequest(char data[64]);

int handleControllerRequest(char data[64]);

int handleMouseRequest(char data[64]);

#endif