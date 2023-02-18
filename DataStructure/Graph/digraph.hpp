#ifndef __DIGRAPH_HPP__
#define __DIGRAPH_HPP__
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <list>
using namespace std;

class Digraph {
public:
    // 从配置文件读入顶点和边信息 生成邻接表
    void readFile(const string& filePath);
    // 输出邻接表信息
    void show() const;
    // 深度优先遍历
    void dfs();
    // 广度优先遍历
    void bfs();

private:
    // 顶点类型
    struct Vertic {
        Vertic(string data)
            : data_(data) { }

        string    data_;    // 存储顶点的信息
        list<int> adjList_; // 邻接链表的结构
    };

private:
    void dfs(int start, vector<bool>& visited);

private:
    vector<Vertic> vertics; // 邻接表结构
};

#endif // !__DIGRAPH_HPP__