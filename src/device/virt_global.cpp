#include "../../include/device/virt_global.hpp"
#include "../../include/debug/debug.hpp"

#include <linux/uinput.h>
#include <unistd.h>

void VirtualDevice::emit(int fd, int type, int code, int value){
    std::lock_guard<std::mutex> lock(m_safe_acc_mtx);
    struct input_event event{};
    event.type = type;
    event.code = code;
    event.value = value;
    write(fd, &event, sizeof(event));
}

void destroy_virt_device(int fd){
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

VirtualDevice::~VirtualDevice(){
    if (this->device_fd != -1){ destroy_virt_device(this->device_fd);}
}

VirtualDevice::VirtualDevice(VirtualDevice&& other) noexcept{
    this->device_fd = other.device_fd;
    other.device_fd = -1;
}
VirtualDevice& VirtualDevice::operator=(VirtualDevice&& other) noexcept{
    if (this != &other){
        if (this->device_fd != -1){ destroy_virt_device(this->device_fd);}
        this->device_fd = other.device_fd;
        other.device_fd = -1;
    }
    return *this;
}