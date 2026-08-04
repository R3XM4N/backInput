#ifndef INSTRUCTIONS_MOUSE_HPP
#define INSTRUCTIONS_MOUSE_HPP

#include "instructions_global.hpp"

/// @brief Holds instruction format for the virtual mouse
namespace INSTR_MOUSE{
    #pragma pack(push, 1)

    struct mouse_btn_up{
        uint8_t device_id = 0;
        uint8_t action_id = 0;
        uint16_t btn_code = 0;
    };

    struct mouse_btn_down{
        uint8_t device_id = 0;
        uint8_t action_id = 1;
        uint16_t btn_code = 0;
    };

    struct mouse_btn_press{
        uint8_t device_id = 0;
        uint8_t action_id = 2;
        uint8_t hold_flag = 0;
        uint16_t btn_code = 0;
    };
    
    struct mouse_move_x{
        uint8_t device_id = 0;
        uint8_t action_id = 3;
        int32_t value = 0;
    };

    struct mouse_move_y{
        uint8_t device_id = 0;
        uint8_t action_id = 4;
        int32_t value = 0;
    };

    #pragma pack(pop)
}

#endif