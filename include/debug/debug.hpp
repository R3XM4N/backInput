#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include <mutex>
#include <atomic>

#include "../net/instructions/msg_definition.hpp"

#define LOG_LOCATION_TEMP   "temp.log"
#define LOG_LOCATION_SAVED  "latest.log"

class LogManager
{
private:
    mutable std::mutex m_safe_acc_mtx;
    bool m_print_cout = false;
    /// @brief Is logging active?
    std::atomic<bool> m_log_flag = false;
    
    /// HELLA ENSURE IT'S A ONE AND ONLY part 1
    LogManager(/* args */)  = default;
    ~LogManager()           = default;
public:
    void log_start();
    void log_stop();
    /// @brief Returns the current state of logging either on or off
    /// @return bool state of the logging state 1 active 0 off
    bool getLogState() { return m_log_flag.load();}

    /// @brief Sets the state of cout writing
    /// @param value The desired state (1/true on or 0/false for off)
    void enable_cout(bool value);

    void write_log(std::string text);
    void write_log(std::string text, int number);

    static LogManager& instance();
    /// HELLA ENSURE IT'S A ONE AND ONLY part 2
    LogManager(const LogManager&)               = delete;
    LogManager& operator=(const LogManager&)    = delete;
    LogManager(const LogManager&&)              = delete;
    LogManager& operator=(const LogManager&&)   = delete;
};

#endif