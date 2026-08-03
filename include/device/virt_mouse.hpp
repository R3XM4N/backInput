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
    /// @brief Sends a move input on the X axis
    /// @param value How much should it move
    void moveX(const int32_t value);
    /// @brief Sends a move input on the Y axis
    /// @param value How much should it move
    void moveY(const int32_t value);
    /// @brief Sets the mouse button into the held/pressed position
    /// @param BTN_CODE Code of the button key
    void buttonDown(const uint16_t BTN_CODE);
    /// @brief Sets the mouse button into the released/depressed position
    /// @param BTN_CODE Code of the button key
    void buttonUp(const uint16_t BTN_CODE);
    /// @brief Clicks a button on the mouse
    /// @param BTN_CODE Code of the button key
    void buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME = 0);
    
    // Wrappers
    /// @brief Sends a vertical move input
    /// @param value How much should it move
    void moveVertically(const int32_t value);
    /// @brief Sends a horizontal move input
    /// @param value How much should it move
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