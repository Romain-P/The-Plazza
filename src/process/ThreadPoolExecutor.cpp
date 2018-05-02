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

            _condition.wait(lock, [this] { return !_pending.empty() || !running(); });
            {
                lock_t locks(_state_mutex);
                _states[std::this_thread::get_id()] = true;
            }
            if (!running()) break;
             task = _pending.front();
            _pending.pop_front();
        }
        task();
        {
            lock_t locks(_state_mutex);
            _states[std::this_thread::get_id()] = false;
        }
    }
}

void ThreadPoolExecutor::stop() {
    lock_t lock(_locker);
    _stop = true;
}

void ThreadPoolExecutor::await_stop() {
    if (running()) return;

    _condition.notify_all();
    for (std::thread &t: _pool)
        t.join();
}

bool ThreadPoolExecutor::running() {
    lock_t lock(_locker);
    return !_stop;
}

bool ThreadPoolExecutor::working() {
    lock_t lock(_state_mutex);

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
