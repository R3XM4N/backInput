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

/// @brief Holds instruction format for the service instructions
namespace INSTR_SYSTEM{
    struct isntr_header{
        uint8_t type_byte;
        uint8_t data_length_byte;
    };
    
}

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

/// @brief Holds instruction format for the virtual controller
namespace INSTR_CONTROLLER{
    #pragma pack(push, 1)
    struct controller_btn_up{
        uint8_t device_id = 0;
        uint8_t action_id = 0;
        uint16_t btn_code = 0;
    };

    struct controller_btn_down{
        uint8_t device_id = 0;
        uint8_t action_id = 1;
        uint16_t btn_code = 0;
    };

    struct controller_btn_press{
        uint8_t device_id = 0;
        uint8_t action_id = 2;
        uint8_t hold_flag = 0;
        uint16_t btn_code = 0;
    };

    struct controller_stick_x{
        uint8_t device_id = 0;
        uint8_t action_id = 3;
        uint8_t right_flag = 0;
        int16_t value = 0;
    };

    struct controller_stick_y{
        uint8_t device_id = 0;
        uint8_t action_id = 4;
        uint8_t right_flag = 0;
        int16_t value = 0;
    };

    struct controller_trigger{
        uint8_t device_id = 0;
        uint8_t action_id = 5;
        uint8_t right_flag = 0;
        uint16_t value = 0;
    };
    #pragma pack(pop)
}

#endif