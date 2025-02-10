#include <iostream>
#include "Guard.hpp"
#include "Singleton.hpp"

using namespace std;
int main() {
    Singleton<int>* singleton = Singleton<int>::getInstance();
    *singleton = 42;
    std::cout << "Singleton integer value: "  << **singleton << std::endl;

    Singleton<int>* anotherSingleton = Singleton<int>::getInstance();
    std::cout << "Another Singleton integer value: " << **anotherSingleton << std::endl;

    Singleton<string>* stringSingleton = Singleton<string>::getInstance();
    *stringSingleton = "string example";
    std::cout << "Singleton string value: " << **stringSingleton << std::endl;

    Singleton<string>* anotherStringSingleton = Singleton<string>::getInstance();
    std::cout <<  "Another Singleton string value: " << **anotherStringSingleton << std::endl; //returns the same  value as stringSingleton
    
    // Create a mutex
    std::mutex mtx;
    {
        Guard guard(mtx); // Lock the mutex
        std::cout << "Inside the guarded section." << std::endl;
        // Perform thread-safe operations here
        if(mtx.try_lock()) {
            std::cout << "Mutex is locked , Guard didn't locked in constructor" << std::endl;
        } else {
            std::cout << "Mutex is already locked by Guard" << std::endl;
        }
    } // Mutex is automatically released when guard goes out of scope, to check this we are trying to lock the mutex again with try_lock

    std::cout << "Outside the guarded section." << std::endl;
    if(mtx.try_lock()) {
        std::cout << "Mutex is locked now, after Guard relased in destructor" << std::endl;
    } else {
        std::cout << "Mutex is already locked, Guard didn't realase" << std::endl;
    }
    mtx.unlock(); // Explicitly unlock the mutex to avoid deadlock due to unguarded mutex

    
    return 0;
} 
