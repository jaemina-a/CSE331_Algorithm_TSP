#include "christo.h"
#include "utils.h"

using namespace std;

vector<int> mst_2based::primMST() {
    int n = this->n;
    vector<double> key(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);
    set<int> inMST;

    key[0] = 0.0;

    for (int count = 0; count < n; ++count) {
        // key값이 최소인 정점을 찾기
        double minKey = numeric_limits<double>::max();
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (inMST.find(v) == inMST.end() && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        inMST.insert(u);

        // key 및 parent 갱신
        for (int v = 0; v < n; ++v) {
            if (inMST.find(v) == inMST.end()) {
                double weight = distance(vertexes[u], vertexes[v]);
                if (weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
    }

    return parent;
}

// DFS로 preorder walk를 수행하고 결과 경로를 저장
void mst_2based::preorderDFS(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& tour) {
    visited[u] = true;
    tour.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            preorderDFS(v, adj, visited, tour);
        }
    }
}

// MST-based 2-approximation TSP 경로 반환
vector<int> mst_2based::tspApproximation() {
    int n = this->n;
    vector<int> parent = primMST();

    // MST의 adjacency list 생성
    vector<vector<int>> adj(n);
    for (int v = 1; v < n; ++v) {
        adj[v].push_back(parent[v]);
        adj[parent[v]].push_back(v);
    }

    // preorder walk
    vector<bool> visited(n, false);
    vector<int> tour;
    preorderDFS(0, adj, visited, tour);

    // TSP 투어를 위해 마지막에 시작점 추가
    tour.push_back(0);
    return tour;
}

void mst_2based::func(){
    vector<int> result_path = tspApproximation();
    int res = 0;
    for(int i=0; i<result_path.size()-1; i++){
        res += distance(vertexes[result_path[i]], vertexes[result_path[i+1]]);
    }
    std::cout << res << std::endl;
}
