#include "ThreadPool.h"

ThreadPool& ThreadPool::request() {
    static ThreadPool tp;
    return tp;
}

void ThreadPool::start() {
    shouldTerminate = false;
    const unsigned int nThreads = std::thread::hardware_concurrency();
    for (unsigned int i = 0; i < nThreads; ++i) {
        threads.emplace_back(std::thread(&ThreadPool::threadLoop, this));
    }
}

void ThreadPool::threadLoop() {
    // we don't want to make the threads stop looking for jobs
    while (true) {
        std::function<void()> job;
        {
            // lock thread's access to jobs queue
            std::unique_lock<std::mutex> lock(jobsMutex);
            
            // stop locking until there is job available or 
            // the thread loop stops
            // avoids unnecessary CPU usage/consumption 
            mutexCondition.wait(lock, [this] {
                return !jobsQueue.empty() || shouldTerminate;
            });
            
            // thread pool stops, then terminate
            if (shouldTerminate) { return; }

            // extract job
            job = jobsQueue.front();
            jobsQueue.pop();
        }
        job();
    }
}

bool ThreadPool::isBusy() {
    bool busy;
    {
        std::unique_lock<std::mutex> lock(jobsMutex);
        busy = !jobsQueue.empty();
    }
    return busy;
}

void ThreadPool::stop() {
    // notify all threads that should terminate
    {
        std::unique_lock<std::mutex> lock(jobsMutex);
        shouldTerminate = true;
    }

    // join and clear all threads
    mutexCondition.notify_all();
    for (std::thread& thread: threads) {
        thread.join();
    }
    threads.clear();
}

ThreadPool::ThreadPool() :
    threads(), jobsQueue(), jobsMutex(), mutexCondition(), shouldTerminate(true)
{}
