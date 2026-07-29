#ifndef VIRT_MOUSE_HPP
#define VIRT_MOUSE_HPP

#include <cinttypes>

#define MOUSE_ACTION_BTN_UP     (uint8_t)0;
#define MOUSE_ACTION_BTN_DOWN   (uint8_t)1;
#define MOUSE_ACTION_BTN_PRESS  (uint8_t)2;
#define MOUSE_ACTION_BTN_MV_X   (uint8_t)3;
#define MOUSE_ACTION_BTN_MV_Y   (uint8_t)4;
#define MOUSE_ACTION_BTN_MV_H   MOUSE_ACTION_BTN_MV_X
#define MOUSE_ACTION_BTN_MV_V   MOUSE_ACTION_BTN_MV_Y
#define MOUSE_ACTION_L_UP       (uint8_t)5;
#define MOUSE_ACTION_L_DOWN     (uint8_t)6;
#define MOUSE_ACTION_L_PRESS    (uint8_t)7;
#define MOUSE_ACTION_R_UP       (uint8_t)8;
#define MOUSE_ACTION_R_DOWN     (uint8_t)9;
#define MOUSE_ACTION_R_PRESS    (uint8_t)10;

class VirtualMouse
{
private:
    int device_fd;
public:
    void moveX(const int32_t value);
    void moveY(const int32_t value);
    void buttonDown(const uint16_t BTN_CODE);
    void buttonUp(const uint16_t BTN_CODE);
    void buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME = 0);
    
    // Wrappers
    void moveVertically(const int32_t value);
    void moveHorizontally(const int32_t value);

    void leftBTNDown();
    void leftBTNUp();
    void leftBTNPress(const uint8_t HOLD_TIME = 0);

    void rightBTNDown();
    void rightBTNUp();
    void rightBTNPress(const uint8_t HOLD_TIME = 0);

    VirtualMouse();
    ~VirtualMouse();
};

#endif