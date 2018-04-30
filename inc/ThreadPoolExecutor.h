//
// Created by romain on 30/04/18.
//

#ifndef PLAZZA_THREADPOOL_H
#define PLAZZA_THREADPOOL_H


#include <deque>
#include <functional>
#include <condition_variable>
#include <vector>
#include <thread>

using task_t = std::function<void()>;

class ThreadPoolExecutor {
public:
    explicit ThreadPoolExecutor(size_t thread_count) :
            _pool(),
            _size(thread_count),
            _pending(),
            _condition(),
            _stop(false) {}

    void init();
    void stop();
    void await_stop();
    bool running();
    void execute(task_t task);
private:
    size_t _size;
    std::vector<std::thread> _pool;
    std::deque<task_t> _pending;
    std::condition_variable _condition;
    std::mutex _unique;
    std::mutex _locker;
    bool _stop;

    void run();
};


#endif //PLAZZA_THREADPOOL_H
