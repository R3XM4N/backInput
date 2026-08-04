#ifndef VIRT_GLOBAL_HPP
#define VIRT_GLOBAL_HPP

void emit(int fd, int type, int code, int value);
void destroy_virt_device(int fd);

class VirtualDevice 
{
protected:
    int device_fd = -1;
    VirtualDevice() = default;
public:
    virtual ~VirtualDevice();
    // NO COPY 
    VirtualDevice(const VirtualDevice& other) = delete;
    VirtualDevice& operator=(const VirtualDevice& other) = delete;
    // YES MOVE
    VirtualDevice(VirtualDevice&& other) noexcept;
    VirtualDevice& operator=(VirtualDevice&& other) noexcept;
private:
};

#endif