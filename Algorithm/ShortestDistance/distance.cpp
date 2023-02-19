#include "distance.hpp"
#include <limits.h>
#include <iostream>
using namespace std;

int dijkstra(const vector<vector<uint>>& graph, int start, int end) {
    // 存储各个顶点的最短路径
    vector<uint> dis(graph.size(), 0);
    vector<bool> used(graph.size(), false);

    used[start] = true;
    // 初始化start到其它U集合顶点权值
    for (int i = 0; i < graph.size(); ++i) {
        dis[i] = graph[start][i];
    }

    for (int i = 1; i < graph.size(); ++i) {
        // 从U集合选择权值最小的顶点
        int idx = -1;
        int min = INT_MAX;
        for (int j = 0; j < graph.size(); ++j) {
            if (!used[j] && min > dis[j]) {
                min = dis[j];
                idx = j;
            }
        }

        if (idx == -1) {
            break;
        }

        // 将选择的顶点加入到S集合中
        used[idx] = true;

        // 更新U集合中剩下顶点的权值信息
        for (int j = 0; j < graph.size(); ++j) {
            if (!used[j] && min + graph[idx][j] < dis[j]) {
                dis[j] = min + graph[idx][j];
            }
        }
    }

    for (int val : dis) {
        cout << val << " ";
    }
    cout << endl;

    return dis[end];
}

int dijkstra_plus(const vector<vector<uint>>& graph, int start, int end) {
    // 存储各个顶点的最短路径
    vector<uint> dis(graph.size(), 0);
    vector<bool> used(graph.size(), false);

    MinHeap que;

    used[start] = true;
    // 初始化start到其它U集合顶点权值
    for (int i = 0; i < graph.size(); ++i) {
        dis[i] = graph[start][i];
        // 将除start顶点之外的其余顶点全部放入到小根堆中
        if (i != start) {
            que.emplace(graph[start][i], i);
        }
    }

    while (!que.empty()) {
        // 从U集合选择权值最小的顶点
        auto elem = que.top();
        que.pop();
        if (elem.first == INT_MAX) {
            break;
        }
        int idx = elem.second;
        int min = elem.first;

        if (used[idx]) continue;
        // 将选择的顶点加入到S集合中
        used[idx] = true;

        // 更新U集合中剩下顶点的权值信息
        for (int j = 0; j < graph.size(); ++j) {
            if (!used[j] && min + graph[idx][j] < dis[j]) {
                dis[j] = min + graph[idx][j];
                que.emplace(dis[j], j);
            }
        }
    }

    for (int val : dis) {
        cout << val << " ";
    }
    cout << endl;

    return dis[end];
}