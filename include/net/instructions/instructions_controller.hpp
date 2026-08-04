#ifndef INSTRUCTIONS_CONTROLLER_HPP
#define INSTRUCTIONS_CONTROLLER_HPP

#include "instructions_global.hpp"

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