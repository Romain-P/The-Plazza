//
// Created by romain on 30/04/18.
//

#include <Shared.h>
#include "ThreadPoolExecutor.h"

void ThreadPoolExecutor::init() {
    for (size_t i=0; i < _size; ++i)
        _pool.emplace_back(&ThreadPoolExecutor::run, this);
}

void ThreadPoolExecutor::run() {
    task_t task;

    while (running()) {
        {
            unique_lock_t lock(_unique);

            _condition.wait(lock, [this] { return !_pending.empty(); });
             task = _pending.front();
            _pending.pop_front();
        }
        task();
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

void ThreadPoolExecutor::execute(task_t task) {
    _pending.push_back(task);
}
