/**
 * @file Singleton.h
 * @brief 单例模式的实现
 * @details 其中包括懒汉式、饿汉式、双检锁机制以及 IoDH 模式
 * @author Leaos
 * @date 2022-10-20
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#if defined(_WIN32) || defined(_WIN64)

#include <mutex>
typedef std::mutex Mutex;

#elif __linux__

#include <pthread_mutex.h>
typedef pthread_mutex_t Mutex;

#endif

/// @brief 普通单例模式
class Singleton {
public:
    static Singleton* getInstance() {
        return _instance;
    }

private:
    Singleton() {
        _instance = new Singleton;
    }

    static Singleton* _instance;
};

/// @brief 饿汉式单例类
class EagerSingleton {
public:
    static EagerSingleton* getInstance() { return _instance; }

private:
    EagerSingleton();
    static EagerSingleton* _instance;
};

/// @brief 懒汉式单例类 通过互斥锁确保线程安全 使用双检锁机制
class LazySingleton {
public:
    static LazySingleton* getInstance() {
        if (_instance == nullptr) {
            _mutex.lock();
            if (_instance == nullptr) {
                _instance = new LazySingleton();
            }
            _mutex.unlock();
        }
        return _instance;
    }

private:
    LazySingleton();
    static LazySingleton* _instance;
    static Mutex          _mutex;
};

/// @brief IoDH单例类
class IoDHSingleton {
public:
    static IoDHSingleton* getInstance() {
        static IoDHSingleton instance;
        return &instance;
    }

private:
    IoDHSingleton();
};

#endif // !_SINGLETON_H_