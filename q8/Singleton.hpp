#ifndef SINGLETON_HPP 
#define SINGLETON_HPP

#include <mutex>

template <typename T>
class Singleton {
private:
    static Singleton<T>* instance;
    static std::mutex mtx;
    Singleton() = default;
    static void cleanup() {
       mtx.lock();
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
        mtx.unlock();
    }
    T value;

public:

    static Singleton<T>* getInstance() {
        if (instance == nullptr) {
            mtx.lock();
            if (instance == nullptr) {
                instance = new Singleton<T>();
                std::atexit(cleanup);
            }
            mtx.unlock();
        }
        return instance;
    }

    T& operator*() {
        return value;
    }
    const T& operator*() const {
        return value;
    }

    T& operator=(const T& val) {
        mtx.lock();
        this->value = val;
        mtx.unlock();
        return this->value;
    }


    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

template <typename T>
Singleton<T>* Singleton<T>::instance = nullptr;

template <typename T>
std::mutex Singleton<T>::mtx;

#endif // SINGLETON_HPP