#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <functional>

#include "../net/instructions/msg_definition.hpp"

int handleSystemRequest(const uint8_t* data);

std::function<void()> handleKeyboardRequest(const uint8_t* data);

std::function<void()> handleControllerRequest(const uint8_t* data);

std::function<void()> handleMouseRequest(const uint8_t* data);

#endif