#include "../../include/net/net.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../include/net/process.hpp"

int local_socket(std::string socket_fd_path){
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    // strcpy(addr.sun_path, "/tmp/vinput.sock");
    strcpy(addr.sun_path, socket_fd_path.c_str());


    unlink(socket_fd_path.c_str());
    bind(socket_fd, (sockaddr*)&addr, sizeof(addr));
    listen(socket_fd, 5);
    
    return socket_fd;
}

void run_process(int local_socket_fd){
    ini_all_devices();
    while (true){
        int client = accept(local_socket_fd, nullptr, nullptr);
        char buffer[64];
        read(client, buffer, sizeof(buffer));
        buffer[63] = '\0';
        
        //temp
        if (buffer[SYS_BYTE_POS_TYPE] == 0){
            if (buffer[1] == (char)255 && buffer[4] == (char)255){
                handleSystemRequest(buffer);
                std::cout << "END SIGNAL RECIEVED\n";
                break;
            }
            handleSystemRequest(buffer);
        }
        else if(buffer[SYS_BYTE_POS_TYPE] == 1){
            handleKeyboardRequest(buffer);
        }
        else if(buffer[SYS_BYTE_POS_TYPE] == 2){
            handleMouseRequest(buffer);
        }
        else if(buffer[SYS_BYTE_POS_TYPE] == 3){
            handleControllerRequest(buffer);
        }
        else{
            std::cout << "Error invalid type\n";
        }
        close(client);
    }
    kill_all_devices();
}