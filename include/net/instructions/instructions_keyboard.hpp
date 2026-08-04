#ifndef INSTRUCTIONS_KEYBOARD_HPP
#define INSTRUCTIONS_KEYBOARD_HPP

#include "instructions_global.hpp"

/// @brief Holds instruction format for the virtual keyboard
namespace INSTR_KEYBOARD{
    #pragma pack(push, 1)

    struct keyboard_key_down{
        uint8_t  device_id   = 0;
        uint8_t  action_id   = 1;
        uint8_t  hold_flag   = 0;
        uint8_t  shift_flag  = 0;
        uint16_t key_code    = 0;
    };
    struct keyboard_key_up{
        uint8_t  device_id   = 0;
        uint8_t  action_id   = 0;
        uint8_t  hold_flag   = 0;
        uint8_t  shift_flag  = 0;
        uint16_t key_code    = 0;
    };
    struct keyboard_key_press{
        uint8_t  device_id   = 0;
        uint8_t  action_id   = 2;
        uint8_t  hold_flag   = 0;
        uint8_t  shift_flag  = 0;
        uint16_t key_code    = 0;
    };

    #pragma pack(pop)
}

#endif