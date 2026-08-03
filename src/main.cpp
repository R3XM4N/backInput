#include <iostream>
#include <unistd.h>
#include <linux/uinput.h>

#include "../include/device/virt_keyboard.hpp"
#include "../include/device/virt_mouse.hpp"
#include "../include/device/virt_controller.hpp"
#include "../include/device/virt_global.hpp"
#include "../include/net/net.hpp"


int main(int argc, char** argv){
    // int keyboard = init_keyboard();
    // usleep(100000);
    // sleep(4);
    // keyHoldSecond(keyboard, KEY_A, 4);
    // destroy_virt_device(keyboard);

    // int mouse = init_mouse();
    // usleep(100000);
    // sleep(4);
    // mouseMoveH(mouse, 1000);
    // destroy_virt_device(mouse);

    int server_fd = local_socket("/tmp/vinput.sock");
    run_process(server_fd);
    

    return EXIT_FAILURE;
}