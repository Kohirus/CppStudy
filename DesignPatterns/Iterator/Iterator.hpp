/**
 * @file Iterator.hpp
 * @brief 迭代器模式
 * @author Leaos
 * @date 2022-11-30
 */

#ifndef _ITERATOR_H_
#define _ITERATOR_H_

class Iterator;
class ConcreteIterator;

/// @brief 抽象聚合类
class Aggregate {
public:
    Aggregate()                       = default;
    virtual Iterator createIterator() = 0;
};

/// @brief 具体的聚合类
class ConcreteAggregate : public Aggregate {
public:
    ConcreteAggregate() = default;
    virtual Iterator cretateIterator() override;
};

/// @brief 抽象迭代器
class Iterator {
public:
    virtual void    first()     = 0; // 将游标指向第一个元素
    virtual void    next()      = 0; // 将游标指向下一个元素
    virtual bool    hasNext()   = 0; // 判断是否存在下一个元素
    virtual Object& operator*() = 0; // 获取游标指向的当前元素
};

/// @brief 具体的迭代器
class ConcreteIterator : public Iterator {
public:
    ConcreteIterator(ConcreteAggrete* objects);

    virtual void    first() override;
    virtual void    next() override;
    virtual bool    hasNext() override;
    virtual Object& operator*() override;

private:
    // 维持一个对具体聚合对象的引用，以便于访问存储在聚合对象中的数据
    ConcreteAggregate* objects;
    int                cursor; // 定义一个游标，用于记录当前的访问位置
};

#endif // !_ITERATOR_H_