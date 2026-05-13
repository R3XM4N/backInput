#include "../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>

void emit(int fd, int type, int code, int value){
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