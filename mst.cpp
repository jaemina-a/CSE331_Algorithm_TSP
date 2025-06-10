#include <vector>
#include "christo.h"
#include "utils.h"

void christofied::MST() {
    std::vector<std::pair<int, int>> min_dist(n); // {parent, cost}
    std::vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        min_dist[i].second = distance(vertexes[0], vertexes[i]);
        min_dist[i].first = 0;
    }

    min_dist[0].second = 0;
    min_dist[0].first = -1; // 0번은 루트
    visited[0] = true;
    for (int count = 1; count < n; count++) {
        int u = -1;
        int min_val = INT32_MAX;

        // 가장 가까운 정점 선택
        for (int v = 0; v < n; v++) { //min_dist에서 visited되지 않은 녀석들중 고른다
            if (!visited[v] && min_dist[v].second < min_val) {
                min_val = min_dist[v].second;
                u = v;
            }
        }
        
        visited[u] = true;
        int parent = min_dist[u].first;
        if (parent != -1) {
            vertexes[parent].connected.push_back(u);
            vertexes[u].connected.push_back(parent);
            this->mst_sum += min_val;
            // std::cout << "mst += " << min_val << std::endl;
        }
        // 거리 갱신
        for (int v = 0; v < n; v++) {
            if(visited[v]){
                continue;
            }
            int d = distance(vertexes[u], vertexes[v]);
            if (!visited[v] && d < min_dist[v].second) {
                min_dist[v] = {u, d};
            }
        }
    }
}
