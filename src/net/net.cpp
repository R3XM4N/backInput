#include "../../include/net/net.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstddef>
#include <cstdint>

#include "../../include/net/process.hpp"
#include "../../include/system/debug.hpp"
#include "../../include/controls/instructions.hpp"

bool read_exact(int fd, void* buffer, uint8_t length){
    uint8_t total_read = 0;
    char* ptr = static_cast<char*>(buffer);

    while (total_read < length) {
        ssize_t bytes_read = read(fd, ptr + total_read, length - total_read);
        if (bytes_read <= 0) {
            return false;
        }
        total_read += static_cast<uint8_t>(bytes_read);
    }
    return true;
}

int local_socket(std::string socket_fd_path){
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_fd_path.c_str(), sizeof(addr.sun_path) -1);

    unlink(socket_fd_path.c_str());
    bind(socket_fd, (sockaddr*)&addr, sizeof(addr));
    listen(socket_fd, 5);
    
    return socket_fd;
}

void run_process(int local_socket_fd){
    loggingStart();

    bool running_flag = true; // I am in great pain but lazy to make a more elegant solution screw those few bits
    while (running_flag){
        int client = accept(local_socket_fd, nullptr, nullptr);
        if (client < 0) continue;

        while (true){
            
            instruction_header recieved_header;
            if (!read_exact(client, &recieved_header, sizeof(instruction_header))){
                logCharPtr("Intruction header has not been recieved fully. Murdering Client.");
                break;
            }
    
            uint8_t i_type = std::to_integer<uint8_t>(recieved_header.instruction_type);
            uint8_t i_length = std::to_integer<uint8_t>(recieved_header.instruction_length);
            
            if (i_type == 0 && i_length == 0){
                logCharPtr("END SIGNAL RECIEVED");
                std::cout << "END SIGNAL RECIEVED\n";
                running_flag = false;
                break;
            }
            
            uint8_t recieved_data[256];
            if (i_length > 0){
                if (!read_exact(client, recieved_data, i_length)){
                    logCharPtr("Intruction data has not been recieved fully. Proceeding with client murder.");
                    break;
                }   
            }
            
            // TO RE-ADD:
            //     handleSystemRequest(buffer);
            //     handleMouseRequest(buffer);
            //     handleControllerRequest(buffer);
            //     std::cout << "Error invalid type\n";

            if (i_type == 1){
                handleKeyboardRequest(recieved_data);
            }    
            
        }
        close(client);
    }
    logStop();
}