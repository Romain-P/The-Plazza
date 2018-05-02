//
// Created by romain on 02/05/18.
//

#include <Shared.h>
#include "Timer.h"

std::thread &Timer::start() {
    _thread = std::thread(&Timer::run, this);
    return _thread;
}

void Timer::run() {
    {
        write_lock_t lock(_locker);
        _running = true;
    }
    while (running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
        _callback();
    }
}

bool Timer::running() {
    read_lock_t lock(_locker);
    return _running;
}

void Timer::stop() {
    write_lock_t lock(_locker);
    _running = false;
}

std::thread &Timer::getThread() {
    return _thread;
}
