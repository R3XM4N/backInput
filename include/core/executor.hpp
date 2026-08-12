#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <queue>
#include <unordered_map>
#include <functional>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

class Executor
{
public:
    /// @brief Describes how/when commands are dequed and executed
    enum class Mode{
        manual,         // executor nneeds to be called to execute commands/calls
        time_auto,      // executor auto starts and manages until changed
        time_manual,   // executor has to be started and can be stopped manually
        instant
    };
    Executor(/* args */);
    ~Executor();
    /// @brief Enques the given command into the queue (queue may be specified)
    /// @param action the call that is to be enqueued
    /// @param queue_name name of the queue to be added to
    void enqueue(std::function<void()> action, std::string queue_name = "default");
    /// @brief  Executes/Runs the frontmost command/call in a queue
    /// @param queue_name The queue that is to be affected
    void execute(std::string queue_name = "default");
    /// @brief Dequeues the frontmost command/call in the queue without triggering/executing it
    /// @param queue_name The name of the desired queue
    void dequeue(std::string queue_name = "default");
    /// @brief Returns the current mode of operation
    /// @return Current mode
    Mode getMode() const {return m_mode;}
    /// @brief Changes the mode of operation to a new mode 
    void changeMode(Mode new_mode);

private:
    /// @brief Flag if the executor is itself responsible for executing commands
    std::atomic<bool> m_independent_flag{false};
    std::thread m_ex_worker;
    std::unordered_map<std::string, std::queue<std::function<void()>>> m_managed_queues;
    /// @brief Holds which queues are to be autoexecuted while auto exec mode is active (timer etc)
    std::vector<std::string> m_auto_managed_vec;
    Mode m_mode;
    /// @brief Execute interval (how often task to be executed)
    std::atomic<uint16_t> m_ex_interval{100};
    /// @brief ensures singular command/call execute thread safe accesss
    mutable std::mutex m_mtx_access;
    /// @brief ensures singular and thread safe accesss to managed vector
    mutable std::mutex m_mtx_vector_acc;


    
    void self_start();
    void self_stop();
    void self_execute(std::string queue_name = "default");
};

#endif