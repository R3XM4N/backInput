#include <sys/socket.h> // socket, connect
#include <sys/un.h>     // sockaddr_un
#include <unistd.h>     // write, close
#include <stdio.h>
#include <string>
#include <iostream>
#include <linux/uinput.h>
#include <cinttypes>

#include "../include/net/instructions/instructions_all.hpp"

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

    //-----------------------KEYBOARD-----------------------

    INSTR_KEYBOARD::keyboard_key_down cmd0;
    cmd0.key_code = KEY_A;

    std::cout << "size: " << sizeof(cmd0);
    sendHeader(fd, 1, sizeof(cmd0));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd0), sizeof(cmd0));
    
    sleep(2);

    INSTR_KEYBOARD::keyboard_key_up cmd1;
    cmd1.key_code = KEY_A;
    sendHeader(fd, 1, sizeof(cmd1));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd1), sizeof(cmd1));

    sleep(1);

    INSTR_KEYBOARD::keyboard_key_press cmd2;
    cmd2.key_code = KEY_B;
    sendHeader(fd, 1, sizeof(cmd2));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd2), sizeof(cmd2));

    sleep(1);
    //------------------------MOUSE------------------------ 
    
    INSTR_MOUSE::mouse_btn_down cmd3;
    cmd3.btn_code = BTN_RIGHT;
    sendHeader(fd, 2, sizeof(cmd3));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd3), sizeof(cmd3));
    
    usleep(500);

    INSTR_MOUSE::mouse_btn_up cmd4;
    cmd4.btn_code = BTN_RIGHT;
    sendHeader(fd, 2, sizeof(cmd4));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd4), sizeof(cmd4));
    
    sleep(2);

    INSTR_MOUSE::mouse_btn_up cmd5;
    cmd5.btn_code = BTN_LEFT;
    sendHeader(fd, 2, sizeof(cmd5));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd5), sizeof(cmd5));

    sleep(1);

    INSTR_MOUSE::mouse_move_x cmd6;
    cmd6.value = (int32_t)25000;
    sendHeader(fd, 2, sizeof(cmd6));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd6), sizeof(cmd6));

    sleep (1);

    INSTR_MOUSE::mouse_move_y cmd7;
    cmd7.value = (int32_t)-100000;
    sendHeader(fd, 2, sizeof(cmd7));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd7), sizeof(cmd7));

    sleep (1);

    //----------------------CONTROLLER---------------------

    INSTR_CONTROLLER::controller_stick_x cmd8;
    cmd8.value = (int16_t)10000;
    sendHeader(fd, 3, sizeof(cmd8));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd8), sizeof(cmd8));

    sleep(1);
    
    INSTR_CONTROLLER::controller_stick_y cmd9;
    cmd9.value = (int16_t)-40000;
    sendHeader(fd, 3, sizeof(cmd9));
    sendInstruction(fd, reinterpret_cast<const uint8_t*>(&cmd9), sizeof(cmd9));

    sleep(1);

    //-----------------------SYSTEM------------------------


    //------------------------------------------------------

    sendHeader(fd, 0, 0);
    close(fd);
    std::cout << "ran\n";

}