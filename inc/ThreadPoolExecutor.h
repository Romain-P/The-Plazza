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
#include <unordered_map>

using task_t = std::function<void()>;
using working_t = bool;

class ThreadPoolExecutor {
public:
    explicit ThreadPoolExecutor(size_t thread_count) :
            _size(thread_count),
            _pool(),
            _states(),
            _pending(),
            _condition(),
            _unique(),
            _locker(),
            _stop(false) {}

    void init();
    void stop();
    void await_stop();
    bool running();
    bool working();
    void execute(task_t task);
private:
    size_t _size;
    std::vector<std::thread> _pool;
    std::unordered_map<std::thread::id, working_t> _states;
    std::deque<task_t> _pending;
    std::condition_variable _condition;
    std::mutex _unique;
    std::mutex _locker;
    bool _stop;

    void run();
};


#endif //PLAZZA_THREADPOOL_H
