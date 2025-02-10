#include "Guard.hpp"

Guard::Guard(std::mutex& mutex) : mtx(mutex), locked(false) {
    std::cout << "Locking mutex in Guard constructor" << std::endl;
    mtx.lock();
    locked = true;
}

Guard::~Guard() {
    std::cout << "Unlocking mutex in Guard destructor" << std::endl;
    if (locked) {
        mtx.unlock();
    }
}

bool Guard::lock() {
    if (!locked) {
        mtx.lock();
        std::cout << "Locking mutex in Guard::lock" << std::endl;
        locked = true;
        return true;
    }
    std::cout << "Mutex already locked" << std::endl;
    return false;
}

bool Guard::unlock() {
    if (locked) {
        std::cout << "Unlocking mutex in Guard::unlock" << std::endl;
        mtx.unlock();
        locked = false;
        return true;
    }
    std::cout << "Mutex already unlocked" << std::endl;
    return false;
}