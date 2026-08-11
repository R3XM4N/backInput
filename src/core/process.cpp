#include "../../include/core/process.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../include/device/virt_keyboard.hpp"
#include "../../include/device/virt_mouse.hpp"
#include "../../include/device/virt_controller.hpp"
#include "../../include/device/virt_global.hpp"
#include "../../include/debug/debug.hpp"
#include "../../include/net/instructions/instructions_all.hpp"

VirtualKeyboard     default_keyboard;
VirtualMouse        default_mouse;
VirtualController   default_controller;

int handleSystemRequest(const uint8_t* data){
    // TO DO
    return 0;
}

std::function<void()> handleKeyboardRequest(const uint8_t* data){
    // TO DO THIS IGNORES FLAGS RN I NEED TO REMAKE THE FORMAT HOLD IS REDUNDANT BUT SHIFT NOT
    if (data[1] == (uint8_t)0x00){
        // NO FLAGS JUST RELEASE
        return [key_code = *reinterpret_cast<const uint16_t*>(data + 4)](){
            default_keyboard.keyUp(key_code);
        };
    }
    else if (data[1] == (uint8_t)0x01){
        // NO FLAGS JUST DEPRESS
        return [key_code = *reinterpret_cast<const uint16_t*>(data + 4)](){
            default_keyboard.keyDown(key_code);
        };
    }
    else if (data[1] == (uint8_t)0x02){
        // NO FLAGS JUST PRESS
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00){
            return [key_code = *reinterpret_cast<const uint16_t*>(data + 4)](){
                default_keyboard.keyPress(key_code);
            };
        }
    }
    return [](){ std::cout << "ERROR INVALID KEYBOARD REQUEST FOUND";};
}

std::function<void()> handleMouseRequest(const uint8_t* data){
    if (data[1] == MOUSE_ACTION_BTN_UP){
        // NO FLAGS JUST RELEASE
        return [btn_code = *reinterpret_cast<const uint16_t*>(data + 2)](){
            default_mouse.buttonUp(btn_code);
        };
    }
    else if(data[1] == MOUSE_ACTION_BTN_DOWN){
        // NO FLAGS JUST DEPRESS
        return [btn_code = *reinterpret_cast<const uint16_t*>(data + 2)](){
            default_mouse.buttonDown(btn_code);
        };
    }
    else if(data[1] == MOUSE_ACTION_BTN_PRESS){
        // NO FLAGS JUST PRESS
        if (data[2 == (uint8_t)0x00]){
            return [btn_code = *reinterpret_cast<const uint16_t*>(data + 3)](){
                default_mouse.buttonPress(btn_code);
            };
        }
        // PRESS HOLD FLAG
        else if(data[2 == (uint8_t)0x01]){
            /// PRESS FOR X SECONDS
            return [btn_code = *reinterpret_cast<const uint16_t*>(data + 3), hold_time = *reinterpret_cast<const uint8_t*>(data + 5)](){
                default_mouse.buttonPress(btn_code, hold_time);
            };
        }
    }
    else if(data[1] == MOUSE_ACTION_BTN_MV_X){
        // MOVE X
        return [value = *reinterpret_cast<const int32_t*>(data + 2)](){
            default_mouse.moveX(value);
        };
    }
    else if(data[1] == MOUSE_ACTION_BTN_MV_Y){
        // MOVE Y
        return [value = *reinterpret_cast<const int32_t*>(data + 2)](){
            default_mouse.moveY(value);
        };
    }
    
    // TO DO:
    // M-L
    // M-R
    // SCROLL
    // EXTRAS

    return [](){ std::cout << "ERROR INVALID MOUSE REQUEST FOUND";};
}

std::function<void()> handleControllerRequest(const uint8_t* data){
    if (data[1] == CNTRL_ACTION_BTN_UP){
        // NO FLAGS JUST RELEASE
        return [btn_code = *reinterpret_cast<const uint16_t*>(data + 2)](){
            default_controller.buttonUp(btn_code);
        };
    }
    else if(data[1] == CNTRL_ACTION_BTN_DOWN){
        // NO FLAGS JUST DEPRESS
        return [btn_code = *reinterpret_cast<const uint16_t*>(data + 2)](){
            default_controller.buttonDown(btn_code);
        };
    }
    else if(data[1] == CNTRL_ACTION_BTN_PRESS){
        // NO FLAGS JUST PRESS
        if (data[2 == (uint8_t)0x00]){
            return [btn_code = *reinterpret_cast<const uint16_t*>(data + 3)](){
                default_controller.buttonPress(btn_code);
            };
        }
        // PRESS HOLD FLAG
        else if(data[2 == (uint8_t)0x01]){
            return [btn_code = *reinterpret_cast<const uint16_t*>(data + 3), hold_time = *reinterpret_cast<const uint8_t*>(data + 5)](){
                default_controller.buttonPress(btn_code, hold_time);
            };
        }
    }
    else if(data[1] == CNTRL_ACTION_MOVE_STICK_X){
        // MOVE LEFT STICK X
        if (data[2] == (uint8_t)0x00){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.stickMoveX(value, 0);
            };
        }
        // MOVE RIGHT STICK X
        else if (data[2] == (uint8_t)0x01){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.stickMoveX(value, 1);
            };
        }        
    }
    else if(data[1] == CNTRL_ACTION_MOVE_STICK_Y){
        // MOVE LEFT STICK Y
        if (data[2] == (uint8_t)0x00){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.stickMoveY(value, 0);
            };
        }
        // MOVE RIGHT STICK Y
        else if (data[2] == (uint8_t)0x01){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.stickMoveY(value, 1);
            };
        }
    }
    else if(data[1] == CNTRL_ACTION_SET_TRIGGER){
        // MOVE LEFT TRIGGER VALUE
        if (data[2] == (uint8_t)0x00){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.pressTrigger(value, 0);
            };
        }
        // MOVE RIGHT TRIGGER VALUE
        else if (data[2] == (uint8_t)0x01){
            return [value = *reinterpret_cast<const int16_t*>(data + 3)](){
                default_controller.pressTrigger(value, 1);
            };
        }
    }
    // TO DO:
    // D-PAD
    // A-PAD
    
    return [](){ std::cout << "ERROR INVALID CONTROLLER REQUEST FOUND";};
}
