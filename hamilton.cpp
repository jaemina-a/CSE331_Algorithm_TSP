#include "christo.h"
#include "utils.h"
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>

std::unordered_map<int, std::list<int>> graph;
std::vector<int> euler_circuit;

void christofied::hierholzer() {
    std::cout <<"HIERHOLZER START\n";
    int start  = 0;
    for(int i=0; i<vertexes.size(); i++){
        graph[i] = std::list<int>(vertexes[i].connected.begin(), vertexes[i].connected.end());
    }

    std::stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int v = st.top();

        // 현재 정점에 미방문 간선이 있으면 하나 탐색
        if (!graph[v].empty()) {
            int u = graph[v].front();
            graph[v].pop_front(); // v -> u 간선 제거
            graph[u].remove(v);   // u -> v 간선도 제거 (무방향)
            st.push(u);
        } else {
            // 더 이상 간선이 없다면 경로에 추가
            euler_circuit.push_back(v);
            st.pop();
        }
    }
    std::cout <<"HIERHOLZER FINISH\n";

    // 결과는 역순으로 저장되어 있음 (출력 시 reverse 필요 없음)
}

// 중복 정점 제거하고 처음 등장한 정점만 따라가기
void christofied::hamilton() {

    std::cout <<"HAMILTON START\n";
    std::vector<bool> visited(vertexes.size(), false);
    std::vector<int> path;

    for (int v : euler_circuit) {
        if (!visited[v]) {
            visited[v] = true;
            path.push_back(v);
        }
    }
    // 원래 시작점으로 다시 돌아오면 TSP 근사 경로 완성
    path.push_back(path[0]);
    for(int i=0 ;i<n-1; i++){
        this->tsp_sum += distance(vertexes[path[i]] , vertexes[path[i+1]]);
    }
    this->tsp_sum += distance(vertexes[path[n-1]], vertexes[0]);

    std::cout <<"HAMILTON END\n";
}
