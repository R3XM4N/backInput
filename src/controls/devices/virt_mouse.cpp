#include "../../../include/controls/devices/virt_mouse.hpp"
#include "../../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

VirtualMouse::VirtualMouse(/* args */){
    this->device_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(device_fd, UI_SET_EVBIT, EV_REL);
    ioctl(device_fd, UI_SET_RELBIT, REL_X);
    ioctl(device_fd, UI_SET_RELBIT, REL_Y);
    ioctl(device_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_MIDDLE);
    ioctl(device_fd, UI_SET_EVBIT, EV_SYN);

    struct uinput_setup dev_setup{};
    dev_setup.id.bustype = BUS_USB;
    dev_setup.id.vendor = 0x1234;
    dev_setup.id.product = 0x5679;
    dev_setup.id.version = 1;
    strcpy(dev_setup.name, "Virtual Mouse");

    ioctl(device_fd, UI_DEV_SETUP, &dev_setup);
    ioctl(device_fd, UI_DEV_CREATE);
}

VirtualMouse::~VirtualMouse(){
    destroy_virt_device(this->device_fd);
}

void VirtualMouse::moveX(const int32_t value){
    emit(this->device_fd, EV_REL, REL_X, value);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::moveY(const int32_t value){
    emit(this->device_fd, EV_REL, REL_Y, value);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::buttonDown(const uint16_t BTN_CODE){
    emit(this->device_fd, EV_KEY, BTN_CODE, 1);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::buttonUp(const uint16_t BTN_CODE){
    emit(this->device_fd, EV_KEY, BTN_CODE, 0);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualMouse::buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME){
    this->buttonDown(BTN_CODE);
    if (HOLD_TIME > 0){ sleep(HOLD_TIME); }
    this->buttonUp(BTN_CODE);
}

void VirtualMouse::moveVertically(const int32_t value){ this->moveY(value);}
void VirtualMouse::moveHorizontally(const int32_t value){ this->moveX(value);}
void VirtualMouse::leftBTNDown(){ this->buttonDown(BTN_LEFT); }
void VirtualMouse::leftBTNUp(){ this->buttonUp(BTN_LEFT); }
void VirtualMouse::leftBTNPress(const uint8_t HOLD_TIME){ this->buttonPress(BTN_LEFT, HOLD_TIME); }
void VirtualMouse::rightBTNDown(){ this->buttonDown(BTN_RIGHT); }
void VirtualMouse::rightBTNUp(){ this->buttonUp(BTN_RIGHT); }
void VirtualMouse::rightBTNPress(const uint8_t HOLD_TIME){ this->buttonPress(BTN_RIGHT, HOLD_TIME); }