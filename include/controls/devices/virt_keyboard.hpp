#ifndef VIRT_KEYBOARD_HPP
#define VIRT_KEYBOARD_HPP

#include <string>
#include <cinttypes>

class VirtualKeyboard
{
private:
    int device_fd;
public:
    void keyDown(const uint16_t KEY_CODE);
    void keyUp(const uint16_t KEY_CODE);
    void keyPress(const uint16_t KEY_CODE, const uint8_t HOLD_TIME = 0);
    VirtualKeyboard();
    ~VirtualKeyboard();
};

#endif