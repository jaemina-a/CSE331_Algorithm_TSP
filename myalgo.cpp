#include "christo.h"
#include "utils.h"
void myalgorithm::cycle_make() {
    std::vector<int> degree(n, 0);
    /*가장 가까운 두놈 찾기*/
    for(int i=0; i<n; i++){
        vertexes[i].closeV[0].second = 100000;
        vertexes[i].closeV[1].second = 100000;
    }
    for(int i=0 ;i<n; i++){
        for(int j=0; j<n; j++){
            if(j!= i){
                int w = distance(vertexes[i], vertexes[j]);
                if(w < vertexes[i].closeV[0].second || w < vertexes[i].closeV[1].second){
                    int big = vertexes[i].closeV[0].second > vertexes[i].closeV[1].second ? 0:1;
                    vertexes[i].closeV[big].first = j;
                    vertexes[i].closeV[big].second = w;
                }
            }
        }
    }
    /*1차 연결*/
    int c_c=0;
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(vertexes[i].closeV[0].first == j || vertexes[i].closeV[1].first == j){
                if(vertexes[j].closeV[0].first == i || vertexes[j].closeV[1].first == i){
                    vertexes[i].connected.push_back(j);
                    vertexes[j].connected.push_back(i);
                    degree[i]++;
                    degree[j]++;
                    c_c ++;
                }
            }
            
        }
    }
    std::cout << "connected conunt : "<< c_c << std::endl;
    for(int step=0; step<2; step++){
        for(int i=0;i<n; i++){
            if(degree[i] < 2){
                int minW = 100000;
                int close = -1;
                /*디그리 1인애 기준으로 모든 노드 순회하면서 디그리 2미만인 애들중 가장 작은놈을 찾기*/
                for(int j=0; j<n; j++){
                    if(j!=i && degree[j]<2){
                        int w = distance(vertexes[i],vertexes[j]);
                        bool same = false;
                        for(int z=0; z<vertexes[i].connected.size(); z++){
                            if(vertexes[i].connected[z] == j){
                                same = true;
                                break;
                            }
                        }
                        if(w<minW && !same){
                            minW = w;
                            close = j;
                        }
                    }
                }
                vertexes[i].connected.push_back(close);
                vertexes[close].connected.push_back(i);
                degree[i]++;
                degree[close]++;
                c_c ++;
            }
        }
    }
}
bool myalgorithm::has_open_chain() {
    for(int i = 0; i < n; ++i) {
        if(vertexes[i].connected.size() < 2) {
            // degree 1 이하인 노드가 있으면 열린 경로 (사이클 아님!)
            return true;
        }
    }
    return false; // 모든 노드가 degree 2 → 사이클만 존재
}

void myalgorithm::cycle_cut() {
    std::vector<bool> visited(n, false);
    open_node_pairs.clear(); // 매번 초기화!

    for(int start=0; start<n; ++start) {
        if(visited[start]) continue;

        int current = start;
        int prev = -1;

        int maxWeight = -1;
        int maxU = -1, maxV = -1;

        do {
            visited[current] = true;
            int next = -1;
            for(int neighbor : vertexes[current].connected) {
                if(neighbor != prev) {
                    next = neighbor;
                    int w = distance(vertexes[current], vertexes[neighbor]);
                    if(w > maxWeight) {
                        maxWeight = w;
                        maxU = current;
                        maxV = neighbor;
                    }
                    break;
                }
            }
            prev = current;
            current = next;
        } while(current != start);

        // 가장 긴 간선 제거
        auto& connU = vertexes[maxU].connected;
        auto& connV = vertexes[maxV].connected;
        connU.erase(std::remove(connU.begin(), connU.end(), maxV), connU.end());
        connV.erase(std::remove(connV.begin(), connV.end(), maxU), connV.end());

        // 열린 노드 쌍 기록
        open_node_pairs.push_back({maxU, maxV});
        this->cycle_cnt += 1;
    }
}

void myalgorithm::cycle_connect() {
    std::vector<int> open_nodes;
    for(auto& p : open_node_pairs) {
        open_nodes.push_back(p.first);
        open_nodes.push_back(p.second);
    }

    std::set<std::pair<int, int>> forbidden_edges;
    for(auto& p : open_node_pairs) {
        forbidden_edges.insert({p.first, p.second});
        forbidden_edges.insert({p.second, p.first});
    }

    // 1. 모든 열린 노드 쌍의 간선 생성
    std::vector<Edge> candidate_edges;
    for(size_t i = 0; i < open_nodes.size(); ++i) {
        for(size_t j = i + 1; j < open_nodes.size(); ++j) {
            int u = open_nodes[i];
            int v = open_nodes[j];
            int w = distance(vertexes[u], vertexes[v]);
            candidate_edges.push_back({u, v, w});
        }
    }

    // 2. 오름차순 정렬
    heapSort(candidate_edges);

    // 3. 금지 간선을 제외한 연결
    std::vector<int> degree(n, 0);
    for(int i = 0; i < vertexes.size(); ++i) {
        degree[i] = vertexes[i].connected.size();
    }
    //꼭 사이클 2개가 병합될 필요는 없다. 3개의 사이클이 병합될 수도 있다. //수정필요
    for(auto& e : candidate_edges) {
        if(degree[e.u] < 2 && degree[e.v] < 2) {
            if(forbidden_edges.count({e.u, e.v}) > 0) continue;
            vertexes[e.u].connected.push_back(e.v);
            vertexes[e.v].connected.push_back(e.u);
            degree[e.u]++;
            degree[e.v]++;
        }
    }
    //사이클이 아닌 것이 남아있는지를 확인해야함 -> 홀수개의 사이클이 병합되어 하나의 사이클이 될수도있는것
    //+ 사이클의 개수도 확인해줘야할듯 몇개가 병합되어있는지 확신할수없음.

    // 4. 마지막 열린 노드 두 개는 금지 간선이라도 연결 (사이클 완성!)

    if(has_open_chain()){
        for(auto& e : candidate_edges) {
            if(degree[e.u] < 2 && degree[e.v] < 2) {
                vertexes[e.u].connected.push_back(e.v);
                vertexes[e.v].connected.push_back(e.u);
                degree[e.u]++;
                degree[e.v]++;
                break;
            }
        }
    }
}
int myalgorithm::count_cycle() {
    std::vector<bool> visited(n, false);
    int cycles = 0;

    for(int i=0; i<n; ++i) {
        if(!visited[i]) {
            int current = i;
            int prev = -1;
            do {
                visited[current] = true;
                // 다음 정점 찾기
                int next = -1;
                for(int v : vertexes[current].connected) {
                    if(v != prev) {
                        next = v;
                        break;
                    }
                }
                prev = current;
                current = next;
            } while(current != i);
            cycles++;
        }
    }
    return cycles;
}

void myalgorithm::func(){
    auto start = std::chrono::high_resolution_clock::now();
    cycle_make();
    while(count_cycle()>1){
        cycle_cut();
        cycle_connect();
    }
    auto end = std::chrono::high_resolution_clock::now();
    this->running_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::vector<bool> visited(n, false);
    int current = 0;
    int prev = -1;
    int total_weight = 0;
    std::string result_file_name = this->file_name + "_myalgo_path"; 
    std::string result_directory = "result_path/" + result_file_name;
    std::ofstream outFile(result_directory);
    do {
        visited[current] = true;
        // 다음 정점 찾기
        int next = -1;
        for(int v : vertexes[current].connected) {
            if(v != prev) {
                next = v;
                break;
            }
        }
        outFile << next <<'\n';
        total_weight += distance(vertexes[current], vertexes[next]);
        prev = current;
        current = next;
    } while(current != 0);
    outFile.close();
    std::cout <<"total weight : " << total_weight << std::endl;
    result_file_name = this->file_name + "_myalgo";
    result_directory = "results/"+result_file_name;
    outFile.open(result_directory);
    outFile << "========================\n";
    outFile << "Total cost : " << total_weight<< "\n";
    if(this->answer_exist){
        outFile << "OPTIMAL COST : " <<this->optimal_sum << "\n";
    }
    outFile << "ACTUAL RUNNING TIME : " << this->running_time.count() << "\n";
    outFile << "========================\n";
    outFile.close();
}
