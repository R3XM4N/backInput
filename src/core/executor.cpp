#include "../../include/core/executor.hpp"

void Executor::execute(std::string queue_name){
    m_managed_queues[queue_name].front()();
    m_managed_queues[queue_name].pop();
}

void Executor::enqueue(std::function<void()> command, std::string queue_name){
    m_managed_queues[queue_name].push(std::move(command));
}

Executor::Executor(/* args */){
    this->m_mode = Mode::manual;
}

Executor::~Executor(){

}