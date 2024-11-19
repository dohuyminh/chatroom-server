#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <future>
#include <memory>
#include <functional>

class ThreadPool {
    
public:
    
    static ThreadPool& request();

    void start(); 
    void stop();
    bool isBusy();

    template<class Fn = void, class ...Args>
    auto addTask(Fn&& fn, Args&&... args) -> std::future<decltype(fn(args...))> {
        // bind the function with the arguments
        auto boundFunc = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
        
        // wrap around std::shared_ptr to be able to copy construct/assign
        auto taskPtr = std::make_shared<std::packaged_task<decltype(fn(args...))()>>(boundFunc);

        // wrap the bound object into void lambda
        auto wrapper = [taskPtr]() { (*taskPtr)(); };

        {
            std::unique_lock<std::mutex> lock(jobsMutex);
            jobsQueue.push(wrapper);
            mutexCondition.notify_one();
        }

        // done executing
        return taskPtr->get_future();
    }
    
private:

    // thread loop
    void threadLoop();

    // thread pool components
    std::vector<std::thread> threads;
    std::mutex jobsMutex;
    std::queue<std::function<void()>> jobsQueue;
    std::condition_variable mutexCondition;
    bool shouldTerminate;

    // private constructor
    ThreadPool();

public:
    ThreadPool(ThreadPool const&) = delete;
    void operator=(ThreadPool const&) = delete;

};
