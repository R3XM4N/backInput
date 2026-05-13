#ifndef NET_HPP
#define NET_HPP

#include <string>

int local_socket(std::string socket_fd_path);
void run_process(int local_socket_fd);

#endif