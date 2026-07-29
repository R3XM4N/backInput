#include "../../include/net/process.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../include/controls/devices/virt_keyboard.hpp"
#include "../../include/controls/devices/virt_mouse.hpp"
#include "../../include/controls/devices/virt_controller.hpp"
#include "../../include/controls/virt_global.hpp"
#include "../../include/system/debug.hpp"
#include "../../include/controls/instructions.hpp"

VirtualKeyboard default_keyboard;
VirtualMouse    default_mouse;

int handleSystemRequest(const uint8_t* data){
    // TO DO
    return 0;
}

int handleKeyboardRequest(const uint8_t* data){
    if (data[1] == (uint8_t)0x00){
        // NO FLAGS JUST RELEASE
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00){
            default_keyboard.keyUp(*reinterpret_cast<const uint16_t*>(data + 4));
        }
    }
    else if (data[1] == (uint8_t)0x01){
        // NO FLAGS JUST DEPRESS
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00){
            default_keyboard.keyDown(*reinterpret_cast<const uint16_t*>(data + 4));
        }
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

    // TO DO:
    // MOVE X/Y
    // M-L
    // M-R
    // SCROLL
    // EXTRAS

    return 0;
}

int handleControllerRequest(const uint8_t* data){

    // TO DO:
    // TRIGGERS
    // STICKS
    // BUTTONS
    // D-PAD
    // A-PAD
    
    return 0;
}
