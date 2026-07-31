#ifndef VIRT_CONTROLLER_HPP
#define VIRT_CONTROLLER_HPP

#include <cinttypes>

#define CNTRL_ACTION_BTN_UP         (uint8_t)0;
#define CNTRL_ACTION_BTN_DOWN       (uint8_t)1;
#define CNTRL_ACTION_BTN_PRESS      (uint8_t)2;
#define CNTRL_ACTION_MOVE_STICK_X   (uint8_t)3;
#define CNTRL_ACTION_MOVE_STICK_Y   (uint8_t)4;
#define CNTRL_ACTION_SET_TRIGGER    (uint8_t)5;

class VirtualController
{
private:
    int device_fd;
    /* data */
public:
    /// @brief Moves the controller stick to the desired X position/value
    /// @param value The value that it should be set into. Does clamp on some devices
    /// @param right_flag If it is the right stick
    void stickMoveX(int16_t value, const bool right_flag);
    /// @brief Moves the controller stick to the desired Y position/value
    /// @param value The value that it should be set into does clamp on some devices
    /// @param right_flag If it is the right stick
    void stickMoveY(int16_t value, const bool right_flag);
    /// @brief Presses/Puts the trigger in a certain position
    /// @param value THe position of the trigger. Does clamp on some devices
    /// @param right_flag If it is the right trigger
    void pressTrigger(uint16_t value, const bool right_flag);
    /// @brief Sets the specififed button into the pressed/held position
    /// @param BTN_CODE The code of the button that is to be changed
    void buttonDown(const uint16_t BTN_CODE);
    /// @brief Sets the specififed button into the released/depressed position
    /// @param BTN_CODE The code of the button that is to be changed
    void buttonUp(const uint16_t BTN_CODE);
    /// @brief Clicks a certain button on the device (sets down and up automatically)
    /// @param BTN_CODE The code of the button that is to be changed
    void buttonPress(const uint16_t BTN_CODE, const uint8_t HOLD_TIME = 0);
    /// @brief Constructor 
    VirtualController(/* args */);
    /// @brief Destroys the controller including the fd
    ~VirtualController();
    // TO DO ADD A-PAD D-PAD 
};

#endif