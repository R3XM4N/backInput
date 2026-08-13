#include "../../include/device/virt_keyboard.hpp"
#include "../../include/device/virt_global.hpp"
#include "../../include/debug/debug.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <memory>

// void shiftDown(int fd){
//     emit(fd, EV_KEY, KEY_RIGHTSHIFT, 1);
//     emit(fd, EV_SYN, SYN_REPORT, 0);
// }
// void shiftUp(int fd){
//     emit(fd, EV_KEY, KEY_RIGHTSHIFT, 0);
//     emit(fd, EV_SYN, SYN_REPORT, 0);
// }

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

    m_dev_type = DeviceType::KEYBOARD;

    LogManager::instance().write_log("KEYBOARD X CREATED");
}

void VirtualKeyboard::keyDown(const uint16_t KEY_CODE){
    emit(this->device_fd, EV_KEY, KEY_CODE, 1);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
    LogManager::instance().write_log("KEYBOARD X key down emited: ", KEY_CODE);
}

void VirtualKeyboard::keyUp(const uint16_t KEY_CODE){
    emit(this->device_fd, EV_KEY, KEY_CODE, 0);
    emit(this->device_fd, EV_SYN, SYN_REPORT, 0);
    LogManager::instance().write_log("KEYBOARD X key up emited: ", KEY_CODE);
}

void VirtualKeyboard::keyPress(const uint16_t KEY_CODE, const uint8_t HOLD_TIME){
    this->keyDown(KEY_CODE);
    if (HOLD_TIME > 0){ sleep(HOLD_TIME); }
    this->keyUp(KEY_CODE);
    LogManager::instance().write_log("KEYBOARD X key press emited: ", KEY_CODE);
}

VirtualKeyboard::~VirtualKeyboard(){
    if (this->device_fd != -1) { destroy_virt_device(this->device_fd); }
    LogManager::instance().write_log("KEYBOARD X destroyed");
}

VirtualKeyboard::VirtualKeyboard(VirtualKeyboard&& other) noexcept : VirtualDevice(std::move(other)){
    this->device_fd = other.device_fd;
    other.device_fd = -1;
}
VirtualKeyboard& VirtualKeyboard::operator=(VirtualKeyboard&& other) noexcept{
    if (this != &other){
        VirtualDevice::operator=(std::move(other));
    }
    return *this;
}