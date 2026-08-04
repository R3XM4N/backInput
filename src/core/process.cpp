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

int handleKeyboardRequest(const uint8_t* data){
    // TO DO THIS IGNORES FLAGS RN I NEED TO REMAKE THE FORMAT HOLD IS REDUNDANT BUT SHIFT NOT
    if (data[1] == (uint8_t)0x00){
        // NO FLAGS JUST RELEASE
        default_keyboard.keyUp(*reinterpret_cast<const uint16_t*>(data + 4));
    }
    else if (data[1] == (uint8_t)0x01){
        // NO FLAGS JUST DEPRESS
        default_keyboard.keyDown(*reinterpret_cast<const uint16_t*>(data + 4));
    }
    else if (data[1] == (uint8_t)0x02){
        // NO FLAGS JUST PRESS
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00){
            default_keyboard.keyPress(*reinterpret_cast<const uint16_t*>(data + 4));
        }
    }
    
    return 0;
}

int handleMouseRequest(const uint8_t* data){
    if (data[1] == MOUSE_ACTION_BTN_UP){
        // NO FLAGS JUST RELEASE
        default_mouse.buttonUp(*reinterpret_cast<const uint16_t*>(data + 2));
    }
    else if(data[1] == MOUSE_ACTION_BTN_DOWN){
        // NO FLAGS JUST DEPRESS
        default_mouse.buttonDown(*reinterpret_cast<const uint16_t*>(data + 2));
    }
    else if(data[1] == MOUSE_ACTION_BTN_PRESS){
        // NO FLAGS JUST PRESS
        if (data[2 == (uint8_t)0x00]){
            default_mouse.buttonPress(*reinterpret_cast<const uint16_t*>(data + 3));
        }
        // PRESS HOLD FLAG
        else if(data[2 == (uint8_t)0x01]){
            // default_mouse.buttonPress(*reinterpret_cast<const uint16_t*>(data + 3), blah blah);
        }
    }
    else if(data[1] == MOUSE_ACTION_BTN_MV_X){
        // MOVE X
        default_mouse.moveX(*reinterpret_cast<const int32_t*>(data + 2));
    }
    else if(data[1] == MOUSE_ACTION_BTN_MV_Y){
        // MOVE Y
        default_mouse.moveY(*reinterpret_cast<const int32_t*>(data + 2));
    }
    
    // TO DO:
    // M-L
    // M-R
    // SCROLL
    // EXTRAS

    return 0;
}

int handleControllerRequest(const uint8_t* data){
    if (data[1] == CNTRL_ACTION_BTN_UP){
        // NO FLAGS JUST RELEASE
        default_controller.buttonUp(*reinterpret_cast<const uint16_t*>(data + 2));
    }
    else if(data[1] == CNTRL_ACTION_BTN_DOWN){
        // NO FLAGS JUST DEPRESS
        default_controller.buttonDown(*reinterpret_cast<const uint16_t*>(data + 2));
    }
    else if(data[1] == CNTRL_ACTION_BTN_PRESS){
        // NO FLAGS JUST PRESS
        if (data[2 == (uint8_t)0x00]){
            default_controller.buttonPress(*reinterpret_cast<const uint16_t*>(data + 3));
        }
        // PRESS HOLD FLAG
        else if(data[2 == (uint8_t)0x01]){
            // default_controller.buttonPress(*reinterpret_cast<const uint16_t*>(data + 3), blah blah);
        }
    }
    else if(data[1] == CNTRL_ACTION_MOVE_STICK_X){
        // MOVE LEFT STICK X
        if (data[2] == (uint8_t)0x00){
            default_controller.stickMoveX(*reinterpret_cast<const int16_t*>(data + 3), 0);
        }
        // MOVE RIGHT STICK X
        else if (data[2] == (uint8_t)0x01){
            default_controller.stickMoveX(*reinterpret_cast<const int16_t*>(data + 3), 1);
        }        
    }
    else if(data[1] == CNTRL_ACTION_MOVE_STICK_Y){
        // MOVE LEFT STICK Y
        if (data[2] == (uint8_t)0x00){
            default_controller.stickMoveY(*reinterpret_cast<const int16_t*>(data + 3), 0);
        }
        // MOVE RIGHT STICK Y
        else if (data[2] == (uint8_t)0x01){
            default_controller.stickMoveY(*reinterpret_cast<const int16_t*>(data + 3), 1);
        }
    }
    else if(data[1] == CNTRL_ACTION_SET_TRIGGER){
        // MOVE LEFT TRIGGER VALUE
        if (data[2] == (uint8_t)0x00){
            default_controller.pressTrigger(*reinterpret_cast<const int16_t*>(data + 3), 0);
        }
        // MOVE RIGHT TRIGGER VALUE
        else if (data[2] == (uint8_t)0x01){
            default_controller.pressTrigger(*reinterpret_cast<const int16_t*>(data + 3), 1);
        }
    }
    // TO DO:
    // D-PAD
    // A-PAD
    
    return 0;
}
