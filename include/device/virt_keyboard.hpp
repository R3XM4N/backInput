#ifndef VIRT_KEYBOARD_HPP
#define VIRT_KEYBOARD_HPP

#include <string>
#include <cinttypes>

#include "virt_global.hpp"

class VirtualKeyboard : public VirtualDevice
{
private:
    // int device_fd;
public:
    /// @brief Set's the key into the held position
    /// @param KEY_CODE code of the desired key
    void keyDown(const uint16_t KEY_CODE);
    /// @brief Set's the key into the released position
    /// @param KEY_CODE code of the desired key
    void keyUp(const uint16_t KEY_CODE);
    /// @brief Clicks the key
    /// @param KEY_CODE code of the desired key
    void keyPress(const uint16_t KEY_CODE, const uint8_t HOLD_TIME = 0);

    explicit VirtualKeyboard();
    ~VirtualKeyboard();

    // NO COPY 
    VirtualKeyboard(const VirtualKeyboard& other) = delete;
    VirtualKeyboard& operator=(const VirtualKeyboard& other) = delete;
    // YES MOVE
    VirtualKeyboard(VirtualKeyboard&& other) noexcept;
    VirtualKeyboard& operator=(VirtualKeyboard&& other) noexcept;
};

#endif