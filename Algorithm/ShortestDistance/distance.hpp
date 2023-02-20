#ifndef __DISTANCE_HPP__
#define __DISTANCE_HPP__

#include <vector>
#include <queue>
using namespace std;

using uint    = unsigned int;
using MinHeap = priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>>;

// 迪杰斯特拉算法
int dijkstra(const vector<vector<uint>>& graph, int start, int end);

// 采用小根堆优化后的迪杰斯特拉算法
int dijkstra_plus(const vector<vector<uint>>& graph, int start, int end);

// 弗洛伊德算法
void floyd(vector<vector<uint>>& graph);

#endif // !__DISTANCE_HPP__