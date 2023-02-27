#ifndef __KRUSKAL_HPP__
#define __KRUSKAL_HPP__

#include <vector>
using namespace std;

struct Edge {
    Edge(char s, char e, int c)
        : start(s)
        , end(e)
        , cost(c) { }

    char start; // 边的起点
    char end;   // 边的终点
    int cost;  // 边的权值
};

class UnionFind {
public:
    UnionFind(int size);

    // 查询
    int find(int num);
    // 合并
    bool merge(int num1, int num2);

private:
    vector<int> nums;
};
#endif // !__KRUSKAL_HPP__