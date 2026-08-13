#include "../../include/debug/debug.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <mutex>

void loggingStart(){
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::filesystem::remove(LOG_LOCATION_TEMP);
    }
    std::ofstream log(LOG_LOCATION_TEMP);
    if (log.is_open()){
        time_t now = time(0);
        log << "LOG STARTED: " << ctime(&now) << '\n';
        log.close();
    }
    
}

void logRecieved(char data[SOCKET_SIZE_WHOLE]){
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::ofstream log(LOG_LOCATION_TEMP, std::ios::app);
        if (log.is_open()){
            time_t now = time(0);
            log << "TIME: " << ctime(&now) << '\n';
            log << "DATA RECIEVED START:\n";
            log << "SYS HEADER:\n";
            log << "Byte " << SYS_BYTE_POS_TYPE << " (TYPE):   [" << (int)data[SYS_BYTE_POS_TYPE]            << "]\n"; 
            log << "Byte " << SYS_BYTE_POS_ID   << " (ID):     [" << (int)data[SYS_BYTE_POS_ID]              << "]\n";
            log << "Byte " << SYS_BYTE_POS_2    << " (NONE 0): [" << (int)data[SYS_BYTE_POS_2]               << "]\n";
            log << "Byte " << SYS_BYTE_POS_3    << " (NONE 1): [" << (int)data[SYS_BYTE_POS_3]               << "]\n";
            log << "DEVICE HEADER:\n";
            log << "Byte " << DEVICE_BYTE_POS_INPUT << " (INPUT T): [" << (int)data[DEVICE_BYTE_POS_INPUT]   << "]\n"; 
            log << "Byte " << DEVICE_BYTE_POS_MOD   << " (ID):      [" << (int)data[DEVICE_BYTE_POS_MOD]     << "]\n";
            log << "Byte " << DEVICE_BYTE_POS_TIME  << " (TIME):    [" << (int)data[DEVICE_BYTE_POS_TIME]    << "]\n";
            log << "Byte " << DEVICE_BYTE_POS_7     << " (NONE 0):  [" << (int)data[DEVICE_BYTE_POS_7]       << "]\n";
            log << "MESSAGE CONTENT:\n";
            log << data + SOCKET_HEADER_SIZE << '\n';
            log << "DATA RECIEVED END:\n";
            log.close();
        }
    }
}

void logCharPtr(char* data){
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::ofstream log(LOG_LOCATION_TEMP, std::ios::app);
        if (log.is_open()){
            time_t now = time(0);
            log << "TIME: " << ctime(&now) << '\n';
            log << data << '\n';
            log.close();
        }
    }
}

void logStop(){
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::ofstream log(LOG_LOCATION_TEMP, std::ios::app);
        if (log.is_open()){
            time_t now = time(0);
            log << "LOG ENDED: " << ctime(&now) << '\n';
            log.close();
        }
    }
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::filesystem::copy_file(LOG_LOCATION_TEMP, LOG_LOCATION_SAVED, std::filesystem::copy_options::overwrite_existing);
    }
    
}