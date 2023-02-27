#ifndef __UNION_FIND_HPP__
#define __UNION_FIND_HPP__

#include <vector>
using namespace std;

class UnionFind {
public:
    UnionFind(int size);

    // 查询
    int find(int num);
    // 合并
    void merge(int num1, int num2);
    // 打印
    void print();

private:
    vector<int> nums;
    vector<int> ranks;
};

#endif // !__UNION_FIND_HPP__