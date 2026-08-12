#include "../../include/core/executor.hpp"

#include <chrono>

#include <iostream>

void Executor::execute(std::string queue_name){
    self_execute(queue_name);
}

void Executor::enqueue(std::function<void()> command, std::string queue_name){
    std::lock_guard<std::mutex> lock(this->m_mtx_access);
    m_managed_queues[queue_name].push(std::move(command));
}

Executor::Executor(/* args */){
    this->m_mode = Mode::manual;
}

Executor::~Executor(){
    self_stop();
}

void Executor::self_start(){
    if (this->m_independent_flag.load()){
        return;
    }
    m_independent_flag.store(true);

    this->m_ex_worker = std::thread([this](){
        while (m_independent_flag.load()){
            { /// MUTEX GUARD BEGIN
                /// MANAGED LIST CHECK IF NONE DEFAULT TO DEFAULT QUEUE
                std::lock_guard<std::mutex> lock(m_mtx_vector_acc);
                if (m_auto_managed_vec.size() <= 0) { self_execute(); }
                else{
                    for (std::string &i : m_auto_managed_vec){
                        self_execute(i);
                    }
                }
            } /// MUTEX GUARD END
            std::this_thread::sleep_for(std::chrono::milliseconds(m_ex_interval.load()));
        }
    });
}

void Executor::self_stop(){
    m_independent_flag.store(false);
    if (m_ex_worker.joinable()){
        m_ex_worker.join();
    }
    
}

void Executor::self_execute(std::string queue_name){
    std::lock_guard<std::mutex> lock(this->m_mtx_access);
    if (m_managed_queues[queue_name].size() <= 0){
        return;
    }
    m_managed_queues[queue_name].front()();
    m_managed_queues[queue_name].pop();
}

void Executor::changeMode(Mode new_mode){
    std::lock_guard<std::mutex> lock(this->m_mtx_access);
    if (m_mode == Mode::time_auto || m_mode ==  Mode::time_manual){
        self_stop();
    }
    if (new_mode == Mode::time_auto || new_mode ==  Mode::time_manual){
        if (new_mode == Mode::time_auto){
            self_start();
        }
        
    }
    
    m_mode = new_mode;
}