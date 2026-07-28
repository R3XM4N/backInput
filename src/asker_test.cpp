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
    close(fd);
    std::cout << "ran\n";

}