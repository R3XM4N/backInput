#ifndef VIRT_CONTROLLER_HPP
#define VIRT_CONTROLLER_HPP

#define CNTRLR_TRIGGER  (char)0 // event type triggers 
#define CNTRLR_STICK_X  (char)1 // event type stick
#define CNTRLR_STICK_Y  (char)2 // event type stick
#define CNTRLR_BTN      (char)3 // event type button

#define CNTRLR_MOD_NONE char(0) // no modifier
#define CNTRLR_MOD_OTHER char(1) // modifier Right? (is the target right side cntrl?)

/// @brief Initializes a virtual controller uinput (fake xbox 360)
/// @return Returns file descriptor for the uinput controller device
int init_controller();
/// @brief Changes the desired analog sticks position on the X axis
/// @param fd controller device file descriptor
/// @param value what should the position (value) be 
/// @param right if the desired stick is on the right
void controllerMoveStickX(int fd, int value, bool right = 0);
/// @brief Changes the desired analog sticks position on the Y axis
/// @param fd controller device file descriptor
/// @param value what should the position (value) be 
/// @param right if the desired stick is on the right
void controllerMoveStickY(int fd, int value, bool right = 0);
/// @brief Changes the value of the press/hold position of the desired trigger
/// @param fd controller device file descriptor
/// @param value what should the position (value) be 
/// @param right if the desired stick is on the right
void controllerPressTrigger(int fd, int value, bool right = 0);
/// @brief Presses a button on the virtual controller (sets value to 1)
/// @param fd controller device file descriptor
/// @param code button code
/// @param u_delay how long in usleep should the device wait for the input to register
void controllerPress(int fd, int code, int u_delay = 0);
/// @brief Releases a button on the virtual controller (sets value to 0)
/// @param fd controller device file descriptor
/// @param code button code
void controllerRelease(int fd, int code);
/// @brief Clicks a button on the virtual controller
/// @param fd controller device file descriptor
/// @param code button code
/// @param u_delay how long in usleep should the device wait for the input to register
void controllerClick(int fd, int code, int u_delay = 0);
/// @brief Holds a virtual controller button for n seconds
/// @param fd controller device file descriptor
/// @param code button code
/// @param seconds for how many seconds should the button be held for
void controllerHold(int fd, int code, int seconds);

#endif