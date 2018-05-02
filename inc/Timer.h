//
// Created by romain on 02/05/18.
//

#ifndef PLAZZA_TIMER_H
#define PLAZZA_TIMER_H


#include <thread>
#include <chrono>
#include <shared_mutex>

class Timer {
public:
    template<class Rep, class Period>
    Timer(std::function<void()> callback, const std::chrono::duration<Rep, Period> &duration) :
            _callback(callback),
            _thread(),
            _delay(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()),
            _running(false)
    {};

    Timer() = default;

    Timer &operator=(Timer &&t) {
        _delay = t._delay;
        _callback = t._callback;
    }

    std::thread &start();
    bool running();
    void stop();
    std::thread &getThread();
private:
    ssize_t _delay;
    std::thread _thread;
    std::function<void()> _callback;
    bool _running;
    std::shared_mutex _locker;

    void run();
};


#endif //PLAZZA_TIMER_H
