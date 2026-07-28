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

// TO DO REPLACE LOW PRIO
VirtualKeyboard default_keyboard;
int MOUSE_FD = -1;
int CONTROLLER_FD = -1;

// TO DO REPLACE LOW PRIO
bool active_dev[3] = {0,0,0}; // devices available

// TO DO REPLACE LOW PRIO
void ini_all_devices(){
    std::cout << "CREATED DEVICES\n";
    MOUSE_FD = init_mouse();
    CONTROLLER_FD = init_controller();
    active_dev[0] = 1;active_dev[1] = 1;active_dev[2] = 1;
}

// TO DO REPLACE LOW PRIO
void kill_all_devices(){
    std::cout << "DESTROYED DEVICES\n";
    if (active_dev[1]) destroy_virt_device(MOUSE_FD);
    if (active_dev[2]) destroy_virt_device(CONTROLLER_FD);
    active_dev[0] = 0;active_dev[1] = 0;active_dev[2] = 0;
}

int handleSystemRequest(const uint8_t* data){
    // TO DO
    return 0;
}

int handleKeyboardRequest(const uint8_t* data){
    if (data[1] == (uint8_t)0x00){
        // NO FLAGS JUST RELEASE
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00 && data[4] == (uint8_t)0x00){
            default_keyboard.keyUp(*reinterpret_cast<const uint16_t*>(data + 5));
        }
    }
    else if (data[1] == (uint8_t)0x01){
        // NO FLAGS JUST DEPRESS
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00 && data[4] == (uint8_t)0x00){
            default_keyboard.keyDown(*reinterpret_cast<const uint16_t*>(data + 5));
        }
    }
    else if (data[1] == (uint8_t)0x02){
        // NO FLAGS JUST PRESS
        if (data[2] == (uint8_t)0x00 && data[3] == (uint8_t)0x00 && data[4] == (uint8_t)0x00){
            default_keyboard.keyPress(*reinterpret_cast<const uint16_t*>(data + 5));
        }
    }
    
    return 0;
}

int handleMouseRequest(const uint8_t* data){
    if (active_dev[1] == 0){
        return 1;
        std::cout << "NO MICE AVAIBLE\n";
    }
    
    // TO DO:
    // MOVE X/Y
    // M-L
    // M-R
    // SCROLL
    // EXTRAS

    return 0;
}

int handleControllerRequest(const uint8_t* data){
    if (active_dev[2] == 0){
        return 1;
        std::cout << "NO CONTROLLERS AVAIBLE\n";
    }
    
    // TO DO:
    // TRIGGERS
    // STICKS
    // BUTTONS
    // D-PAD
    // A-PAD
    
    return 0;
}
