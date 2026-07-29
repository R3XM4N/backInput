#include "../../../include/controls/devices/virt_keyboard.hpp"
#include "../../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>


// /// @brief Holds the key in pressed for n seconds
// /// @param fd keyboard device file descriptor
// /// @param code key code
// /// @param seconds amount of seconds to hold for
// void keyHoldSecond(int fd, int code, int seconds){
//     keyDown(fd, code);
//     sleep(seconds);
//     keyUP(fd, code);
// }

// void shiftDown(int fd){
//     emit(fd, EV_KEY, KEY_RIGHTSHIFT, 1);
//     emit(fd, EV_SYN, SYN_REPORT, 0);
// }
// void shiftUp(int fd){
//     emit(fd, EV_KEY, KEY_RIGHTSHIFT, 0);
//     emit(fd, EV_SYN, SYN_REPORT, 0);
// }

// static const int key_table[26] { KEY_A, 
//     KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, 
//     KEY_G, KEY_H, KEY_I, KEY_J, KEY_K,
//     KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
//     KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
//     KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z
// };

VirtualKeyboard::VirtualKeyboard(/* args */)
{
    this->device_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(this->device_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(this->device_fd, UI_SET_EVBIT, EV_SYN);
    for (int i = 0; i < KEY_MAX; i++){
        ioctl(this->device_fd, UI_SET_KEYBIT, i);
    }
    
    struct uinput_setup dev_setup{};
    dev_setup.id.bustype = BUS_USB;
    dev_setup.id.vendor = 0x1234;
    dev_setup.id.product = 0x5678;
    dev_setup.id.version = 1;
    strcpy(dev_setup.name, "Virtual Keyboard");
    
    ioctl(this->device_fd, UI_DEV_SETUP, &dev_setup);
    ioctl(this->device_fd, UI_DEV_CREATE);
}

void VirtualKeyboard::keyDown(const uint16_t KEY_CODE){
    emit(this->device_fd, EV_KEY, KEY_CODE, 1);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualKeyboard::keyUp(const uint16_t KEY_CODE){
    emit(this->device_fd, EV_KEY, KEY_CODE, 0);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualKeyboard::keyPress(const uint16_t KEY_CODE, const uint8_t HOLD_TIME){
    this->keyDown(KEY_CODE);
    if (HOLD_TIME > 0){ sleep(HOLD_TIME); }
    this->keyUp(KEY_CODE);
}

VirtualKeyboard::~VirtualKeyboard(){
    destroy_virt_device(this->device_fd);
}