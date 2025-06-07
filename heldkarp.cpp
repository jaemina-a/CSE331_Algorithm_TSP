
#include <vector>
#include <unordered_map>
#include <climits>

#include "utils.h"

int n;  // 도시 개수
std::vector<std::vector<int>> cost; // 거리 행렬
std::vector<std::unordered_map<int, int>> dp; // dp[last][mask]

// Top-down 재귀 함수
int tsp(int last, int mask) {
    if (mask == (1 << n) - 1) {
        return cost[last][0]; // 모든 도시 방문 후 0번으로 돌아감
    }

    if (dp[last].count(mask)) return dp[last][mask];

    int min_cost = INT_MAX;
    for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue; // 이미 방문한 도시
        int next_mask = mask | (1 << next);
        int temp = cost[last][next] + tsp(next, next_mask);
        min_cost = std::min(min_cost, temp);
    }

    return dp[last][mask] = min_cost;
}

int solve_tsp_top_down(const std::vector<Vertex>& vertexes_input) {
    n = vertexes_input.size();
    cost.assign(n, std::vector<int>(n));
    dp.assign(n, std::unordered_map<int, int>());

    // 거리 계산
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cost[i][j] = distance(vertexes_input[i], vertexes_input[j]);

    return tsp(0, 1 << 0); // 시작점은 0, 0번 도시만 방문한 상태
}