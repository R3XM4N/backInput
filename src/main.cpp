#include <iostream>
#include <unistd.h>
#include <linux/uinput.h>

#include "../include/device/virt_keyboard.hpp"
#include "../include/device/virt_mouse.hpp"
#include "../include/device/virt_controller.hpp"
#include "../include/device/virt_global.hpp"
#include "../include/net/net.hpp"


int main(int argc, char** argv){

    // TO DO: ARGUMENTS
    int server_fd = local_socket("/tmp/vinput.sock");
    run_process(server_fd);
    

    return EXIT_SUCCESS;
}