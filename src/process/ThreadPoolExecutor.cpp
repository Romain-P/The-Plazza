//
// Created by romain on 30/04/18.
//

#include <Shared.h>
#include "ThreadPoolExecutor.h"

void ThreadPoolExecutor::init() {
    for (size_t i=0; i < _size; ++i) {
        _pool.emplace_back(&ThreadPoolExecutor::run, this);
        _states[_pool.at(i).get_id()] = false;
    }
}

void ThreadPoolExecutor::run() {
    task_t task;

    while (running()) {
        {
            unique_lock_t lock(_unique);

            _condition.wait(lock, [this] { return !_pending.empty(); });
            {
                lock_t locks(_locker);
                _states[std::this_thread::get_id()] = true;
            }
             task = _pending.front();
            _pending.pop_front();
        }
        task();
        {
            lock_t locks(_locker);
            _states[std::this_thread::get_id()] = false;
        }
    }
}

void ThreadPoolExecutor::stop() {
    lock_t lock(_locker);
    _stop = true;
}

void ThreadPoolExecutor::await_stop() {
    lock_t lock(_locker);

    if (!_stop) return;
    for (std::thread &t: _pool)
        t.join();
}

bool ThreadPoolExecutor::running() {
    lock_t lock(_locker);
    return !_stop;
}

bool ThreadPoolExecutor::working() {
    if (!_pending.empty())
        return true;
    bool working = false;
    for (auto &keyset : _states) {
        if (keyset.second) {
            working = true;
            break;
        }
    }
    return working;
}

void ThreadPoolExecutor::execute(task_t task) {
    {
        unique_lock_t lock(_locker);
        _pending.push_back(task);
    }
    _condition.notify_one();
}
