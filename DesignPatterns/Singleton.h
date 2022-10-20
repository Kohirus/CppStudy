#ifndef _SINGLETON_H_
#define _SINGLETON_H_

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

#endif // !_SINGLETON_H_