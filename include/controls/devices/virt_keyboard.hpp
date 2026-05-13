#ifndef VIRT_KEYBOARD_HPP
#define VIRT_KEYBOARD_HPP

#include <string>

#define KEYBOARD_KEY        (char)0 // type of event = key press/hold

#define KEYBOARD_MOD_NONE     (char)0 // no modifier
#define KEYBOARD_MOD_SHIFT    (char)1 // modifier press shift beforehand stop afterwards

/// @brief Initializes a virtual keyboard uinput
/// @return Returns file descriptor for the uinput keyboard device
int init_keyboard();
/// @brief Sets the key to 1 (pressed)
/// @param fd keyboard device file descriptor
/// @param code key code
/// @param delay How long to wait to register in usleep after press
void keyDown(int fd, int code, int delay = 0);
/// @brief Sets the key to 0 (not pressed)
/// @param fd keyboard device file descriptor
/// @param code key code
void keyUP(int fd, int code);
/// @brief Presses the key (both press and release)
/// @param fd keyboard device file descriptor
/// @param code key code
/// @param delay How long to wait to register in usleep after press
void keyPress(int fd, int code, int delay = 0);
/// @brief Holds the key in pressed for n seconds
/// @param fd keyboard device file descriptor
/// @param code key code
/// @param seconds amount of seconds to hold for
void keyHoldSecond(int fd, int code, int seconds);
/// @brief Get's key code for a character warning: scuffed and poorly "made"
/// @param c char
/// @param shift_state state of the shift (capitalization)
/// @return returns the key code
int keyGetCharCode(char c, bool& shift_state);
/// @brief Tries to type the given text
/// @param fd keyboard device file descriptor
/// @param text text to type
/// @param s_delay delay between presses
void keyTypeText(int fd, const std::string &text, int s_delay = 0);

#endif