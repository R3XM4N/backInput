#include <sys/socket.h> // socket, connect
#include <sys/un.h>     // sockaddr_un
#include <unistd.h>     // write, close
#include <stdio.h>
#include <string>
#include <iostream>
#include <linux/uinput.h>
#include <cinttypes>

#include "../include/controls/instructions.hpp"


void sendHeader(int fd, uint8_t type, uint8_t length) {
    instruction_header header;
    header.instruction_type = static_cast<std::byte>(type);
    header.instruction_length = static_cast<std::byte>(length);

    write(fd, &header, sizeof(header));
}

void sendInstruction(int fd, const uint8_t* instruction_data, uint8_t instruction_length) {
    if (!(instruction_length > 0)) {return;}
    write(fd, instruction_data, instruction_length);
}

// void sendRequest(sockaddr_un &addr, char dev_type, char dev_id, char input_type_id, char modifier, char time_mod, std::string instructions){
//     if (instructions.length() >  56){
//         std::cout << "REQUEST TOO LONG\n";
//         return;
//     }
//     int fd = socket(AF_UNIX, SOCK_STREAM, 0);
//     connect(fd, (sockaddr*)&addr, sizeof(addr));

//     char data[64] = {' '};
//     data[0] = dev_type;
//     data[1] = dev_id;
//     data[4] = input_type_id;
//     data[5] = modifier;
//     data[6] = time_mod;
    
//     // snprintf((char*)data + 8, 56, "TEST TEXT %d", 100);
//     snprintf((char*)data + 8, 56, instructions.c_str());

//     write(fd, data, 64);
//     close(fd);
// }

int main(){
    struct sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/vinput.sock"); //socket of the reciever

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    connect(fd, (sockaddr*)&addr, sizeof(addr));


    //--------------------TEST CODE HERE--------------------

    INSTR_KEYBOARD::keyboard_key_down cmd0;
    cmd0.key_code = KEY_A;

    std::cout << "size: " << sizeof(cmd0);
    sendHeader(fd, 1, sizeof(cmd0));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd0), sizeof(cmd0));
    sleep(4);

    INSTR_KEYBOARD::keyboard_key_up cmd1;
    cmd1.key_code = KEY_A;
    sendHeader(fd, 1, sizeof(cmd1));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd1), sizeof(cmd1));
    


    //------------------------------------------------------
    sendHeader(fd, 0, 0);
    // sendInstruction(fd, 0, 0);
    close(fd);
    std::cout << "ran\n";

    // sendRequest(addr, 1, 0, 0, 0, 2, "KEY " + std::to_string(KEY_D) + " HLD 4");
    // sendRequest(addr, 0, 255, 255, 0, 0, "TEST TEXT 100");

    // sleep(4);
    // sendRequest(addr, 1, 0, 0, 0, 0, "KEY " + std::to_string(KEY_W));
    // sendRequest(addr, 1, 0, 0, 0, 1, "KEY " + std::to_string(KEY_A) + " DEL 10000");

    // sendRequest(addr, 2, 0, 0, 0, 0, "MVX " + std::to_string(50));
    // sendRequest(addr, 2, 0, 1, 0, 1, "MVY " + std::to_string(50) + " DEL 10000");
    // sendRequest(addr, 2, 0, 1, 0, 2, "KEY " + std::to_string(550) + " HLD 4");

    // sendRequest(addr, 2, 0, 3, 0, 0, "ML");
    // sendRequest(addr, 2, 0, 4, 0, 1, "MR DEL 10000");
    // sendRequest(addr, 2, 0, 3, 0, 2, "ML HLD 4");

    // sendRequest(addr, 3, 0, 1, 0, 0, "STICK MV X 100000");


}