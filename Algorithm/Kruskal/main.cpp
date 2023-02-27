#include <iostream>
#include <vector>
#include <algorithm>
#include "kruskal.hpp"
using namespace std;

int main() {
    vector<Edge> edges;

    int n = 0;
    cout << "Input count: ";
    cin >> n;

    int  cost;
    char start, end;
    for (int i = 0; i < n; i++) {
        cin >> start >> end >> cost;
        edges.emplace_back(start, end, cost);
    }

    // 按权值大小进行排序
    sort(edges.begin(), edges.end(),
        [](auto& a, auto& b) -> bool {
            return a.cost < b.cost;
        });

    // 从小到大选边
    UnionFind set(200);
    for (int i = 0; i < edges.size(); i++) {
        if (set.merge(edges[i].start, edges[i].end)) {
            cout << edges[i].start << " - " << edges[i].end << " : " << edges[i].cost << endl;
        }
    }

    return 0;
}