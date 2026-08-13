#ifndef VIRT_GLOBAL_HPP
#define VIRT_GLOBAL_HPP

#include <cinttypes>
#include <mutex>

// void emit(int fd, int type, int code, int value);
void destroy_virt_device(int fd);

class VirtualDevice 
{
protected:
    int device_fd = -1;
    uint8_t m_id = 0;
    mutable std::mutex m_safe_acc_mtx;
    VirtualDevice() = default;
    void emit(int fd, int type, int code, int value);
public:
    virtual ~VirtualDevice();
    // NO COPY 
    VirtualDevice(const VirtualDevice& other) = delete;
    VirtualDevice& operator=(const VirtualDevice& other) = delete;
    // YES MOVE
    VirtualDevice(VirtualDevice&& other) noexcept;
    VirtualDevice& operator=(VirtualDevice&& other) noexcept;

    int getID() const { return m_id; }
private:
};

#endif