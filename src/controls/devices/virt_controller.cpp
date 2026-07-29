#include "../../../include/controls/devices/virt_controller.hpp"
#include "../../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

VirtualController::VirtualController(/* args */){
    this->device_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(device_fd, UI_SET_KEYBIT, BTN_SOUTH);
    ioctl(device_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_EAST);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_WEST);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_NORTH);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_TL);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_TR);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_SELECT);
    ioctl(device_fd, UI_SET_KEYBIT, BTN_START);

    // sticks
    ioctl(device_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(device_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(device_fd, UI_SET_ABSBIT, ABS_Y);
    ioctl(device_fd, UI_SET_ABSBIT, ABS_RX);
    ioctl(device_fd, UI_SET_ABSBIT, ABS_RY);
    ioctl(device_fd, UI_SET_EVBIT, EV_SYN);

    struct uinput_abs_setup axis{};
    axis.absinfo.minimum = -32768;
    axis.absinfo.maximum = -32767;
    axis.absinfo.flat = 128;
    axis.absinfo.fuzz = 16;
    axis.code = ABS_X; ioctl(device_fd, UI_ABS_SETUP, &axis);
    axis.code = ABS_Y; ioctl(device_fd, UI_ABS_SETUP, &axis);
    axis.code = ABS_RX; ioctl(device_fd, UI_ABS_SETUP, &axis);
    axis.code = ABS_RY; ioctl(device_fd, UI_ABS_SETUP, &axis);

    // triggers
    ioctl(device_fd, UI_SET_ABSBIT, ABS_Z);
    ioctl(device_fd, UI_SET_ABSBIT, ABS_RZ);

    struct uinput_abs_setup trigger{};
    trigger.absinfo.minimum = 0;
    trigger.absinfo.maximum = 255;
    trigger.absinfo.flat = 0;
    trigger.absinfo.fuzz = 4;
    trigger.code = ABS_Z; ioctl(device_fd, UI_ABS_SETUP, &trigger);
    trigger.code = ABS_RZ; ioctl(device_fd, UI_ABS_SETUP, &trigger);

    struct uinput_setup dev_setup{};
    dev_setup.id.bustype = BUS_USB;
    dev_setup.id.vendor  = 0x045e; // so called 'xbox'
    dev_setup.id.product = 0x028e;
    dev_setup.id.version = 1;
    strcpy(dev_setup.name, "Virtual Controller");

    ioctl(device_fd, UI_DEV_SETUP, &dev_setup);
    ioctl(device_fd, UI_DEV_CREATE);
}

VirtualController::~VirtualController(){
    destroy_virt_device(this->device_fd);
}

void VirtualController::stickMoveX(int16_t value, const bool right_flag){
    if (value > 32767) {value = 32767;}
    if (value < -32768) {value = -32768;}
    if (right_flag){
        emit(this->device_fd, EV_ABS, ABS_RX, value);
    }
    else{
        emit(this->device_fd, EV_ABS, ABS_X, value);
    }
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualController::stickMoveY(int16_t value, const bool right_flag){
    if (value > 32767) {value = 32767;}
    if (value < -32768) {value = -32768;}
    if (right_flag){
        emit(this->device_fd, EV_ABS, ABS_RY, value);
    }
    else{
        emit(this->device_fd, EV_ABS, ABS_Y, value);
    }
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualController::pressTrigger(uint16_t value, const bool right_flag){
    if (value > 255) {value = 255;}
    if (value < 0) {value = 0;}
    if (right_flag){
        emit(this->device_fd, EV_ABS, ABS_RZ, value);
    }
    else{
        emit(this->device_fd, EV_ABS, ABS_Z, value);
    }
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualController::buttonDown(const uint16_t BTN_CODE){
    emit(this->device_fd, EV_KEY ,BTN_CODE, 1);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualController::buttonUp(const uint16_t BTN_CODE){
    emit(this->device_fd, EV_KEY ,BTN_CODE, 0);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
}

void VirtualController::buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME){
    this->buttonDown(BTN_CODE);
    if (HOLD_TIME > 0){ sleep(HOLD_TIME); }
    this->buttonUp(BTN_CODE);
}