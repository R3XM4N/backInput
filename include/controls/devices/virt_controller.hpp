#ifndef VIRT_CONTROLLER_HPP
#define VIRT_CONTROLLER_HPP

#include <cinttypes>

class VirtualController
{
private:
    int device_fd;
    /* data */
public:
    void stickMoveX(int16_t value, const bool right_flag);
    void stickMoveY(int16_t value, const bool right_flag);
    void pressTrigger(uint16_t value, const bool right_flag);
    void buttonDown(const uint16_t BTN_CODE);
    void buttonUp(const uint16_t BTN_CODE);
    void buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME = 0);
    // TO DO ADD A-PAD D-PAD
    VirtualController(/* args */);
    ~VirtualController();
};

#endif