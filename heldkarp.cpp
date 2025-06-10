#include "tsp.h"
#include "utils.h"
#include <cmath>

void heldkarp::run_tsp_helper() {
    int n = vertexes.size();
    int N = 1 << n;
    const double INF = std::numeric_limits<double>::infinity();

    std::vector<std::vector<double>> dp(N, std::vector<double>(n, INF));
    std::vector<std::vector<int>> parent(N, std::vector<int>(n, -1));
    std::vector<std::vector<double>> dist(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = distance(vertexes[i], vertexes[j]);

    dp[1][0] = 0.0; // 시작점 0에서 출발

    for (int mask = 1; mask < N; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!(mask & (1 << last))) continue;
            int prev_mask = mask ^ (1 << last);
            if (prev_mask == 0 && last == 0) continue;
            for (int k = 0; k < n; ++k) {
                if (k == last || !(prev_mask & (1 << k))) continue;
                double new_cost = dp[prev_mask][k] + dist[k][last];
                if (new_cost < dp[mask][last]) {
                    dp[mask][last] = new_cost;
                    parent[mask][last] = k;
                }
            }
        }
    }

    // 최소비용과 마지막 도시 구하기
    double ans = INF;
    int last_city = -1;
    int full_mask = N - 1;
    for (int last = 1; last < n; ++last) {
        double cost = dp[full_mask][last] + dist[last][0];
        if (cost < ans) {
            ans = cost;
            last_city = last;
        }
    }

    // 경로 복원 (answer에 저장, 0번에서 시작해 0번으로 끝나도록)
    answer.clear();
    answer.push_back(0); // 출발점
    int mask = full_mask;
    int curr = last_city;
    std::vector<int> temp_path;
    while (curr != 0) {
        temp_path.push_back(curr);
        int prev = parent[mask][curr];
        mask ^= (1 << curr);
        curr = prev;
    }
    std::reverse(temp_path.begin(), temp_path.end());
    for (int v : temp_path) answer.push_back(v);
    answer.push_back(0); // 마지막에 출발점으로 복귀
   
    
    this->total_sum = ans;
}