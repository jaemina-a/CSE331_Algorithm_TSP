// #include "christo.h"
#include "utils.h"
#include <cmath>
int distance(const struct Vertex p1, const struct Vertex p2){
    double d1 = p1.x - p2.x;
    double d2 = p1.y - p2.y;
    double d = std::sqrt(static_cast<double>(d1*d1 + d2*d2));
    return static_cast<int>(d+0.5);
}


void heapify(std::vector<Edge>& edges, int n, int i) {
    int largest = i; // 루트
    int l = 2*i + 1; // 왼쪽 자식
    int r = 2*i + 2; // 오른쪽 자식

    // 왼쪽 자식이 루트보다 크면
    if(l < n && edges[l].weight > edges[largest].weight)
        largest = l;

    // 오른쪽 자식이 현재 가장 큰 것보다 크면
    if(r < n && edges[r].weight > edges[largest].weight)
        largest = r;

    // largest가 루트가 아니라면 교환
    if(largest != i) {
        std::swap(edges[i], edges[largest]);
        // 재귀적으로 아래 서브트리 heapify
        heapify(edges, n, largest);
    }
}
void heapSort(std::vector<Edge>& edges) {
    int n = edges.size();

    // 힙 생성
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(edges, n, i);

    // 하나씩 최대값을 맨 뒤로 보내면서 정렬
    for(int i = n-1; i > 0; i--) {
        std::swap(edges[0], edges[i]); // 최대값을 뒤로 보냄
        heapify(edges, i, 0); // 나머지에 대해 heapify
    }
}