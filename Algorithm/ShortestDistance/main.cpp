#include <iostream>
#include <vector>
#include <limits.h>
#include "distance.hpp"
using namespace std;

const unsigned int INF = INT_MAX;

int main() {
    vector<vector<unsigned int>> graph = {
        { 0, 6, 3, INF, INF, INF },
        { 6, 0, 2, 5, INF, INF },
        { 3, 2, 0, 3, 4, INF },
        { INF, 5, 3, 0, 2, 3 },
        { INF, INF, 4, 2, 0, 5 },
        { INF, INF, INF, 3, 5, 0 },
    };

    int distance = dijkstra(graph, 0, 3);
    if (distance == INF) {
        cout << "不存在有效路径!" << endl;
    } else {
        cout << "distance:" << distance << endl;
    }
    cout << "=====================" << endl;
    
    distance = dijkstra_plus(graph, 0, 1);
    if (distance == INF) {
        cout << "不存在有效路径!" << endl;
    } else {
        cout << "distance:" << distance << endl;
    }
    cout << "=====================" << endl;
    return 0;
}