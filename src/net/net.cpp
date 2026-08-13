#include "../../include/net/net.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstddef>
#include <cstdint>

#include "../../include/core/process.hpp"
#include "../../include/debug/debug.hpp"
#include "../../include/net/instructions/instructions_all.hpp"
#include "../../include/core/executor.hpp"

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
    LogManager::instance().log_start();
    LogManager::instance().enable_cout(1);

    bool direct_mode = true;    // If executor is to bypassed
    bool running_flag = true;   // I am in great pain but lazy to make a more elegant solution screw those few bits

    Executor local_executor;
    // local_executor.changeMode(Executor::Mode::time_auto);

    while (running_flag){
        int client = accept(local_socket_fd, nullptr, nullptr);
        if (client < 0) continue;

        while (true){
            
            instruction_header recieved_header;
            if (!read_exact(client, &recieved_header, sizeof(instruction_header))){
                LogManager::instance().write_log((char*)"Intruction header has not been recieved fully. Murdering Client.");
                break;
            }
    
            uint8_t i_type = std::to_integer<uint8_t>(recieved_header.instruction_type);
            uint8_t i_length = std::to_integer<uint8_t>(recieved_header.instruction_length);
            
            if (i_type == 0 && i_length == 0){
                LogManager::instance().write_log((char*)"END SIGNAL RECIEVED");
                running_flag = false;
                break;
            }
            
            uint8_t recieved_data[256];
            if (i_length > 0){
                if (!read_exact(client, recieved_data, i_length)){
                    LogManager::instance().write_log((char*)"Intruction data has not been recieved fully. Proceeding with client murder.");
                    break;
                }   
            }

            if( i_type == 0x00){
                // SYSTEM INSTRUCTIONS
            }
            if (direct_mode){
                if(i_type == 0x01){
                    handleKeyboardRequest(recieved_data)();
                }
                else if( i_type == 0x02){
                    handleMouseRequest(recieved_data)();
                }
                else if( i_type == 0x03){
                    handleControllerRequest(recieved_data)();
                }
                else{
                    // TO DO INVALID REPORTING
                }
            }
            else{
                if(i_type == 0x01){
                    local_executor.enqueue(handleKeyboardRequest(recieved_data));
                }
                else if( i_type == 0x02){
                    local_executor.enqueue(handleMouseRequest(recieved_data));
                }
                else if( i_type == 0x03){
                    local_executor.enqueue(handleControllerRequest(recieved_data));
                }
                else{
                    // TO DO INVALID REPORTING
                }
            }
        }
        close(client);
    }
    LogManager::instance().log_stop();
}