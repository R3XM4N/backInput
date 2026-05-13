#include "../../../include/controls/devices/virt_keyboard.hpp"
#include "../../../include/controls/virt_global.hpp"

#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>

int init_keyboard(){
    int device_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(device_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(device_fd, UI_SET_EVBIT, EV_SYN);
    for (int i = 0; i < KEY_MAX; i++){
        ioctl(device_fd, UI_SET_KEYBIT, i);
    }
    
    struct uinput_setup dev_setup{};
    dev_setup.id.bustype = BUS_USB;
    dev_setup.id.vendor = 0x1234;
    dev_setup.id.product = 0x5678;
    dev_setup.id.version = 1;
    strcpy(dev_setup.name, "Virtual Keyboard");
    
    ioctl(device_fd, UI_DEV_SETUP, &dev_setup);
    ioctl(device_fd, UI_DEV_CREATE);

    return device_fd;
}

void keyDown(int fd, int code, int delay){
    emit(fd, EV_KEY, code, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    if (delay > 0) { usleep(delay); }
}

void keyUP(int fd, int code){
    emit(fd, EV_KEY, code, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void keyPress(int fd, int code, int delay){
    keyDown(fd, code, delay);
    keyUP(fd, code);
}

void keyHoldSecond(int fd, int code, int seconds){
    keyDown(fd, code);
    sleep(seconds);
    keyUP(fd, code);
}

void shiftDown(int fd){
    emit(fd, EV_KEY, KEY_RIGHTSHIFT, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}
void shiftUp(int fd){
    emit(fd, EV_KEY, KEY_RIGHTSHIFT, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

static const int key_table[26] { KEY_A, 
    KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, 
    KEY_G, KEY_H, KEY_I, KEY_J, KEY_K,
    KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
    KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
    KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z
};

int keyGetCharCode(char c, bool& shift_state){
    shift_state = false;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        if (c >= 'A' && c <= 'Z') {shift_state = 1;}
        else {c -= 32;}
        c -= 65;
        return key_table[(int)c];
    } 
    
    if (c >= '1' && c <= '9') return KEY_1 + (c - '1');
    switch (c){ // "stolen" basic mapping of generics
        case '0': return KEY_0;
        case ' ': return KEY_SPACE;
        case '\n': return KEY_ENTER;
        case '\t': return KEY_TAB;
        case '!': shift_state = true; return KEY_1;
        case '@': shift_state = true; return KEY_2;
        case '#': shift_state = true; return KEY_3;
        case '$': shift_state = true; return KEY_4;
        case '%': shift_state = true; return KEY_5;
        case '^': shift_state = true; return KEY_6;
        case '&': shift_state = true; return KEY_7;
        case '*': shift_state = true; return KEY_8;
        case '(': shift_state = true; return KEY_9;
        case ')': shift_state = true; return KEY_0;
        case '-': return KEY_MINUS;
        case '_': shift_state = true; return KEY_MINUS;
        case '=': return KEY_EQUAL;
        case '+': shift_state = true; return KEY_EQUAL;
        case '[': return KEY_LEFTBRACE;
        case ']': return KEY_RIGHTBRACE;
        case '{': shift_state = true; return KEY_LEFTBRACE;
        case '}': shift_state = true; return KEY_RIGHTBRACE;
        case ';': return KEY_SEMICOLON;
        case ':': shift_state = true; return KEY_SEMICOLON;
        case '\'': return KEY_APOSTROPHE;
        case '"': shift_state = true; return KEY_APOSTROPHE;
        case ',': return KEY_COMMA;
        case '<': shift_state = true; return KEY_COMMA;
        case '.': return KEY_DOT;
        case '>': shift_state = true; return KEY_DOT;
        case '/': return KEY_SLASH;
        case '?': shift_state = true; return KEY_SLASH;
        case '\\': return KEY_BACKSLASH;
        case '|': shift_state = true; return KEY_BACKSLASH;
        case '`': return KEY_GRAVE;
        case '~': shift_state = true; return KEY_GRAVE;
        default: return -1;
    }
}
void keyTypeText(int fd, const std::string &text, int s_delay){
    for (const char& letter : text){
        bool shift_state;
        if (s_delay){
            sleep(s_delay);
        }
        int key_code = keyGetCharCode(letter, shift_state); 
        if (shift_state){ shiftDown(fd); }
        keyPress(fd , key_code);
        if (shift_state){ shiftUp(fd); }
    }
    
}
