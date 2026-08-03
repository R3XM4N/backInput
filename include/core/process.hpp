#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>

#include "../net/instructions/msg_definition.hpp"

int handleSystemRequest(const uint8_t* data);

int handleKeyboardRequest(const uint8_t* data);

int handleControllerRequest(const uint8_t* data);

int handleMouseRequest(const uint8_t* data);

#endif