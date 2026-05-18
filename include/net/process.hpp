#ifndef PROCESS_HPP
#define PROCESS_HPP

#define SYS_BYTE_POS_TYPE       0 // System message device type byte position
#define SYS_BYTE_POS_ID         1 // System message device id byte position
#define SYS_BYTE_POS_2          2 // System message empty 0 byte position
#define SYS_BYTE_POS_3          3 // System message empty 1 byte position

#define DEVICE_BYTE_POS_INPUT   4 // Device message input type byte position
#define DEVICE_BYTE_POS_MOD     5 // Device message input modifier byte position
#define DEVICE_BYTE_POS_TIME    6 // Device message time modifier byte position
#define DEVICE_BYTE_POS_7       7 // Device message empty 0 byte position

#define HEADER_SIZE             8 // Header size


void coutBytes(char data[64]);
void ini_all_devices();
void kill_all_devices();

int handleSystemRequest(char data[64]);

int handleKeyboardRequest(char data[64]);

int handleControllerRequest(char data[64]);

int handleMouseRequest(char data[64]);

#endif