#include "Singleton.h"

Singleton* Singleton::_instance = nullptr;

EagerSingleton* EagerSingleton::_instance = new Singleton();

LazySingleton* LazySingleton::_instance = nullptr;
#if defined(_WIN32) || defined(_WIN64)
std::mutex LazySingleton::_mutex;
#elif __linux__
pthread_mutex_t LazySingleton::_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif