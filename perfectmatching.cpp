#include "christo.h"
#include <vector>

void christofied::perfect_matching(){
    std::vector<int>odd_vertex;
    for(int i=0; i<vertexes.size(); i++){
        if(this->vertexes[i].connected.size()%2 == 1){
            odd_vertex.emplace_back(i);
        }
    }
    int k = odd_vertex.size();
    std::vector<bool> matched(k,false);
    for(int u=0; u<k; ++u){
        if(matched[u]) continue;
        int bestJ = -1;
        long long bestDist2 = INT32_MAX;
        for(int v=u+1; v<k; ++v){
            if(matched[v]) continue;
            Vertex v_u = this->vertexes[odd_vertex[u]];
            Vertex v_v = this->vertexes[odd_vertex[v]];
            long long dx = v_u.x - v_v.x;
            long long dy = v_u.y - v_v.y;
            long long d2 = dx*dx + dy*dy;     // 제곱 거리
            if(d2 < bestDist2){
                bestDist2 = d2;
                bestJ     = v;
            }
        }
        if(bestJ != -1){
            matched[u] = matched[bestJ] = true;
            this->vertexes[odd_vertex[u]].connected.push_back(odd_vertex[bestJ]);
            this->vertexes[odd_vertex[bestJ]].connected.push_back(odd_vertex[u]);
        }
    }
}
