#pragma once
#include <mutex>

template<typename T>
class MutexedVariable
{
    T _value;

    // mutexes should always be mutable
    mutable std::mutex _mutex;

public:
    MutexedVariable(T value)
    {
        _value = value;
    }

    operator T() const
    {
        std::lock_guard<std::mutex> l(_mutex);
        return _value;
    }

    T operator=(T value)
    {
        std::lock_guard<std::mutex> l(_mutex);
        _value = value;
        return _value;
    }

    T operator+=(T value)
    {
        std::lock_guard<std::mutex> l(_mutex);
        _value += value;
        return _value;
    }
};
