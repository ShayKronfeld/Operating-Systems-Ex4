#pragma once
#include <mutex>
#include <iostream>

class Guard {
private:
    std::mutex& mtx;
    bool locked;

public:
    explicit Guard(std::mutex& mutex);

    bool lock();

    bool unlock();

    ~Guard();

    // Prevent copying and assignment
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;
};