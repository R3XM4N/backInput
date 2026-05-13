#include "../../include/net/process.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../include/controls/devices/virt_keyboard.hpp"
#include "../../include/controls/devices/virt_mouse.hpp"
#include "../../include/controls/devices/virt_controller.hpp"
#include "../../include/controls/virt_global.hpp"

// data[0] = dev_type;
// data[1] = dev_id;
// data[4] = input_type_id;
// data[5] = modifier;
// data[6] = delay/timestamps;

#define TIME_BYTE_NONE       (char)0 // no time modifier
#define TIME_BYTE_DELAY      (char)1 // time modifier wait to register
#define TIME_BYTE_HOLD       (char)2 // time modifier hold state
#define TIME_BYTE_DELAY_HOLD (char)3 // time modifier hold and wait

// temporary solution
int KEYBOARD_FD = -1;
int MOUSE_FD = -1;
int CONTROLLER_FD = -1;

bool active_dev[3] = {0,0,0}; // devices available

void ini_all_devices(){
    std::cout << "CREATED DEVICES\n";
    KEYBOARD_FD = init_keyboard();
    MOUSE_FD = init_mouse();
    CONTROLLER_FD = init_controller();
    active_dev[0] = 1;active_dev[1] = 1;active_dev[2] = 1;
}

void kill_all_devices(){
    std::cout << "DESTROYED DEVICES\n";
    if (active_dev[0]) destroy_virt_device(KEYBOARD_FD);
    if (active_dev[1]) destroy_virt_device(MOUSE_FD);
    if (active_dev[2]) destroy_virt_device(CONTROLLER_FD);
    active_dev[0] = 0;active_dev[1] = 0;active_dev[2] = 0;
}

void coutBytes(char data[64]){
    std::cout   << "data[0]: " << (int)data[0] << "\n"
                << "data[1]: " << (int)data[1] << "\n"
                << "data[2]: " << (int)data[2] << "\n"
                << "data[3]: " << (int)data[3] << "\n"
                << "data[4]: " << (int)data[4] << "\n"
                << "data[5]: " << (int)data[5] << "\n"
                << "data[6]: " << (int)data[6] << "\n"
                << "data[7]: " << (int)data[7] << "\n"
                << "char data[8-63]: " << data + 8 << "\n";
}

int handleSystemRequest(char data[64]){
    char* text = (char*)data + 8;
    int test_int;
    coutBytes(data);

    sscanf(text, "TEST TEXT %d", &test_int);
    // snprintf((char*)cmd + 8, 56, "TEST TEXT %d", 100);
    std::cout << "-" << text << "-" << test_int << "-\n";
    return 0;
}

int handleKeyboardRequest(char data[64]){
    if (active_dev[0] == 0){
        return 1;
        std::cout << "NO KEYBOARDS AVAIBLE\n";
    }
    coutBytes(data);

    if (data[4] == KEYBOARD_KEY){
        if (data[6] == TIME_BYTE_NONE){
            int key_code;
            sscanf((char*)(data + 8), "KEY %d", &key_code);
            keyPress(KEYBOARD_FD, key_code);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int key_code, key_delay;
            sscanf((char*)(data + 8), "KEY %d DEL %d", &key_code, &key_delay);
            keyPress(KEYBOARD_FD, key_code, key_delay);
        }
        else if (data[6] == TIME_BYTE_HOLD){
            int key_code, key_hold;
            sscanf((char*)(data + 8), "KEY %d HLD %d", &key_code, &key_hold);
            keyHoldSecond(KEYBOARD_FD, key_code, key_hold);
        }        
    }
    else{
        std::cout << "KEYBOARD UNRECOGNIZED COMMAND\n";
    }
    
    return 0;
}

int handleMouseRequest(char data[64]){
    if (active_dev[1] == 0){
        return 1;
        std::cout << "NO MICE AVAIBLE\n";
    }
    
    if (data[4] == MOUSE_MOVE_X){
        if (data[6] == TIME_BYTE_NONE){
            int move_value;
            sscanf((char*)(data + 8), "MVX %d", &move_value);
            mouseMoveX(MOUSE_FD, move_value);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int move_value, move_delay;
            sscanf((char*)(data + 8), "MVX %d DEL %d", &move_value, &move_delay);
            mouseMoveX(MOUSE_FD, move_value, move_delay);
        }
    }
    else if (data[4] == MOUSE_MOVE_Y){
        if (data[6] == TIME_BYTE_NONE){
            int move_value;
            sscanf((char*)(data + 8), "MVY %d", &move_value);
            mouseMoveY(MOUSE_FD, move_value);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int move_value, move_delay;
            sscanf((char*)(data + 8), "MVY %d DEL %d", &move_value, &move_delay);
            mouseMoveY(MOUSE_FD, move_value, move_delay);
        }
    }
    else if (data[4] == MOUSE_BTN){
        if (data[6] == TIME_BYTE_NONE){
            int btn_code;
            sscanf((char*)(data + 8), "BTN %d", &btn_code);
            mouseClickBTN(KEYBOARD_FD, btn_code);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int btn_code, btn_delay;
            sscanf((char*)(data + 8), "BTN %d DEL %d", &btn_code, &btn_delay);
            mouseClickBTN(KEYBOARD_FD, btn_code, btn_delay);
        }
        else if (data[6] == TIME_BYTE_HOLD){
            int btn_code, btn_hold;
            sscanf((char*)(data + 8), "BTN %d HLD %d", &btn_code, &btn_hold);
            mouseHoldBTN(KEYBOARD_FD, btn_code, btn_hold);
        }  
    }
    else if (data[4] == MOUSE_BTN_L){
        if (data[6] == TIME_BYTE_NONE){
            mouseClickL(KEYBOARD_FD);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int btn_delay;
            sscanf((char*)(data + 8), "ML DEL %d", &btn_delay);
            mouseClickL(KEYBOARD_FD, btn_delay);
        }
        else if (data[6] == TIME_BYTE_HOLD){
            int  btn_hold;
            sscanf((char*)(data + 8), "ML HLD %d", &btn_hold);
            mouseHoldL(KEYBOARD_FD, btn_hold);
        }
    }
    else if (data[4] == MOUSE_BTN_R){
        if (data[6] == TIME_BYTE_NONE){
            mouseClickR(KEYBOARD_FD);
        }
        else if (data[6] == TIME_BYTE_DELAY){
            int btn_delay;
            sscanf((char*)(data + 8), "MR DEL %d", &btn_delay);
            mouseClickR(KEYBOARD_FD, btn_delay);
        }
        else if (data[6] == TIME_BYTE_HOLD){
            int btn_hold;
            sscanf((char*)(data + 8), "MR HLD %d", &btn_hold);
            mouseHoldR(KEYBOARD_FD, btn_hold);
        }
    }
    else{
        std::cout << "MOUSE UNRECOGNIZED COMMAND\n";
    }
    return 0;
}

int handleControllerRequest(char data[64]){
    if (active_dev[2] == 0){
        return 1;
        std::cout << "NO CONTROLLERS AVAIBLE\n";
    }
    coutBytes(data);

    if (data[4] == CNTRLR_TRIGGER){
        /* code */
    }
    else if (data[4] == CNTRLR_STICK){
        int value;
        sscanf((char*)(data + 8), "STICK MV X %d", &value);
        controllerMoveStickX(CONTROLLER_FD, value);
    }
    else if (data[4] == CNTRLR_BTN){
        
    }
    else{
        std::cout << "CONTROLLER UNRECOGNIZED COMMAND\n";
    }
    
    return 0;
}
