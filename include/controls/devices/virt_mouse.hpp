#ifndef VIRT_MOUSE_HPP
#define VIRT_MOUSE_HPP

#define MOUSE_MOVE_X    (char)0 // event type move x axis
#define MOUSE_MOVE_Y    (char)1 // event type move y axis
#define MOUSE_BTN       (char)2 // event type a button interaction
#define MOUSE_BTN_L     (char)3 // event type left mouse button interaction
#define MOUSE_BTN_R     (char)4 // event type right mouse button interaction

/// @brief Initializes a virtual mouse uinput
/// @return Returns file descriptor for the uinput mouse device
int init_mouse();
/// @brief Moves the mouse horizontaly
/// @param fd mouse device file descriptor
/// @param value value of how much should the device move
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseMoveH(int fd, int value, int u_delay = 0);
/// @brief Moves the mice on the X axis (mouseMoveX alias)
/// @param fd mouse device file descriptor
/// @param value value of how much should the device move
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseMoveX(int fd, int value, int u_delay = 0);
/// @brief Moves the mouse verticaly
/// @param fd mouse device file descriptor
/// @param value value of how much should the device move
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseMoveV(int fd, int value, int u_delay = 0);
/// @brief Moves the mice on the Y axis (mouseMoveV alias)
/// @param fd mouse device file descriptor
/// @param value value of how much should the device move
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseMoveY(int fd, int value, int u_delay = 0);
/// @brief Holds the specified mouse button (set it to 1)
/// @param fd mouse device file descriptor
/// @param code button code
/// @param u_delay usleep delay of how long should device wait for the input to register
void mousePressBTN(int fd, int code, int u_delay = 0);
/// @brief Releases the specified mouse button (set it to 0)
/// @param fd mouse device file descriptor
/// @param code button code
void mouseRelBTN(int fd, int code);
/// @brief Presses the specified mouse button
/// @param fd mouse device file descriptor
/// @param code button code
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseClickBTN(int fd, int code, int u_delay = 0);
/// @brief Holds the specified mouse button (set it to 1)
/// @param fd mouse device file descriptor
/// @param code button code
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseHoldBTN(int fd, int code, int seconds);
/// @brief Clicks the left mouse button
/// @param fd mouse device file descriptor
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseClickL(int fd, int u_delay = 0);
/// @brief Clicks the right mouse button
/// @param fd mouse device file descriptor
/// @param u_delay usleep delay of how long should device wait for the input to register
void mouseClickR(int fd, int u_delay = 0);
/// @brief Holds the left mouse button for n seconds
/// @param fd mouse device file descriptor
/// @param seconds how long should the left mouse button be held for
void mouseHoldL(int fd, int seconds);
/// @brief Holds the right mouse button for n seconds
/// @param fd mouse device file descriptor
/// @param seconds how long should the right mouse button be held for
void mouseHoldR(int fd, int seconds);

#endif