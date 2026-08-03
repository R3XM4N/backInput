#ifndef INTRUCTIONS_ALL_HPP
#define INTRUCTIONS_ALL_HPP

#include <cstddef>
#include <cinttypes>

#pragma pack(push, 1)
struct instruction_header
{
    std::byte instruction_type;
    std::byte instruction_length;
};
#pragma pack(pop)

namespace INSTR_SYSTEM{
    
}

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

namespace INSTR_MOUSE{
    
}

namespace INSTR_CONTROLLER{
    
}

#endif