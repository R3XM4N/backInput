#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <queue>
#include <unordered_map>
#include <functional>
#include <string>


class Executor
{
public:
    /// @brief Describes how/when commands are dequed and executed
    enum class Mode{
        manual,
        time,
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
    std::unordered_map<std::string, std::queue<std::function<void()>>> m_managed_queues;
    Mode m_mode;
};

#endif