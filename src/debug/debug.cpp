#include "../../include/debug/debug.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

void LogManager::write_log(std::string text){
    if (m_log_flag.load() == false){ return;}

    std::lock_guard<std::mutex> lock(m_safe_acc_mtx);

    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::ofstream log(LOG_LOCATION_TEMP, std::ios::app);
        if (log.is_open()){
            time_t now = time(0);
            log << "TIME: " << ctime(&now) << '\n';
            log << text << '\n';
            log.close();
            if (m_print_cout){
                std::cout << ctime(&now) << text << "\n";
            }
        }
    }
}
void LogManager::write_log(std::string text, int number){
    if (m_log_flag.load() == false){ return;}
    write_log(text + std::to_string(number));
}


void LogManager::log_start(){
    if (true ==  m_log_flag.load()){ return;}

    std::lock_guard<std::mutex> lock(m_safe_acc_mtx);

    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::filesystem::remove(LOG_LOCATION_TEMP);
    }
    std::ofstream log(LOG_LOCATION_TEMP);
    if (log.is_open()){
        time_t now = time(0);
        log << "LOG STARTED: " << ctime(&now) << '\n';
        log.close();
        if (m_print_cout){
            std::cout << ctime(&now) << " LOGGING STARTED\n";
        }
    }

    m_log_flag.store(true);
}

void LogManager::log_stop(){
    if (false ==  m_log_flag.load()){ return;}
    
    std::lock_guard<std::mutex> lock(m_safe_acc_mtx);

    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::ofstream log(LOG_LOCATION_TEMP, std::ios::app);
        if (log.is_open()){
            time_t now = time(0);
            log << "LOG ENDED: " << ctime(&now) << '\n';
            log.close();
            if (m_print_cout){
                std::cout << ctime(&now) << " LOGGING ENDED\n";
            }
        }
    }
    if (std::filesystem::exists(LOG_LOCATION_TEMP)){
        std::filesystem::copy_file(LOG_LOCATION_TEMP, LOG_LOCATION_SAVED, std::filesystem::copy_options::overwrite_existing);
    }

    m_log_flag.store(false);
}

void LogManager::enable_cout(bool value){
    std::lock_guard<std::mutex> lock(m_safe_acc_mtx); /// Is it here? Is it not? Well i guess theoretically you can access m_print_cout twice? What an absurd scenario!
    if (value == m_print_cout) { return;}
    m_print_cout = value;
}

LogManager& LogManager::instance(){
    static LogManager logger;
    return logger;
}