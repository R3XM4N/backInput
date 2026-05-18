#ifndef MSG_DEFINITION_HPP
#define MSG_DEFINITION_HPP

#define SYS_BYTE_POS_TYPE       0 // System message device type byte position
#define SYS_BYTE_POS_ID         1 // System message device id byte position
#define SYS_BYTE_POS_2          2 // System message empty 0 byte position
#define SYS_BYTE_POS_3          3 // System message empty 1 byte position

#define DEVICE_BYTE_POS_INPUT   4 // Device message input type byte position
#define DEVICE_BYTE_POS_MOD     5 // Device message input modifier byte position
#define DEVICE_BYTE_POS_TIME    6 // Device message time modifier byte position
#define DEVICE_BYTE_POS_7       7 // Device message empty 0 byte position

#define SOCKET_SIZE_WHOLE           64  // Entire socket/message size

#define SOCKET_HEADER_SIZE          8   // Header size
#define SOCKET_SYS_HEADER_SIZE      4   // System info header size
#define SOCKET_DEVICE_HEADER_SIZE   4   // Device info header size
#define SOCKET_MESSAGE_LENGTH       56  // Maximum length of the message after the header

#define SOCKET_MESSAGE_LAST_BYE     SOCKET_SIZE_WHOLE - 1  // Last byte position of the message/socket

#endif