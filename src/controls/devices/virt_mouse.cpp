#include "../../../include/controls/devices/virt_mouse.hpp"
#include "../../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int init_mouse(){
    int device_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

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

    return device_fd;
}

void mouseMoveH(int fd, int value, int u_delay){
    emit(fd, EV_REL, REL_X, value);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    if (u_delay > 0) { usleep(u_delay); }
}

void mouseMoveV(int fd, int value, int u_delay){
    emit(fd, EV_REL, REL_Y, value);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    if (u_delay > 0) { usleep(u_delay); }
}

void mousePressBTN(int fd, int code, int u_delay){
    emit(fd, EV_KEY, code, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    if (u_delay > 0) { usleep(u_delay); }
}

void mouseRelBTN(int fd, int code){
    emit(fd, EV_KEY, code, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void mouseClickBTN(int fd, int code, int u_delay){
    mousePressBTN(fd, code);
    if (u_delay > 0) { usleep(u_delay); }
    mouseRelBTN(fd, code);
}

void mouseHoldBTN(int fd, int code, int seconds){
    mousePressBTN(fd, code);
    sleep(seconds);
    mouseRelBTN(fd, code);
}

void mouseMoveX(int fd, int value, int u_delay) { mouseMoveH(fd, value, u_delay); }
void mouseMoveY(int fd, int value, int u_delay) { mouseMoveV(fd, value, u_delay); }
void mouseHoldL(int fd, int seconds) { mouseHoldBTN(fd, BTN_LEFT, seconds); }
void mouseHoldR(int fd, int seconds) { mouseHoldBTN(fd, BTN_RIGHT, seconds); }
void mouseClickL(int fd, int u_delay){ mouseClickBTN(fd, BTN_LEFT, u_delay); }
void mouseClickR(int fd, int u_delay){ mouseClickBTN(fd, BTN_RIGHT, u_delay); }
