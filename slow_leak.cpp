/*
 *      _                 _            _    
 *  ___| | _____      __ | | ___  __ _| | __
 * / __| |/ _ \ \ /\ / / | |/ _ \/ _` | |/ /
 * \__ \ | (_) \ V  V /  | |  __/ (_| |   < 
 * |___/_|\___/ \_/\_/   |_|\___|\__,_|_|\_\
 *                                          
 *
 */

#include <bits/stdc++.h>

typedef long long LL;

struct State {
    int v;
    LL c;

    State(int v, LL c) : v{v}, c{c} { }
    bool operator<(const State &other) const { return c < other.c; }
    bool operator>(const State &other) const { return c > other.c; }
};

int main() {

    int N,M,T; LL D; scanf("%d %d %d %lld", &N, &M, &T, &D);
    std::vector<bool> isrepair(N+1); isrepair[1] = true; isrepair[N] = true;
    std::vector<std::vector<LL>> adj(N+1, std::vector<LL>(N+1, -1));
    for (int i = 0; i < T; ++i) {
        int repairstation; scanf("%d", &repairstation);
        isrepair[repairstation] = true;
    }
    for (int i = 0; i < M; ++i) {
        int u,v; LL w; scanf("%d %d %lld", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // Floyd Warshalls All Pairs Shortest Path
    for (int k = 1; k <= N; ++k) {
        for (int u = 1; u <= N; ++u) {
            for (int v = 1; v <= N; ++v) {
                if (adj[u][k] >= 0 && adj[k][v] >= 0) {
                    LL opt = adj[u][k] + adj[k][v];
                    adj[u][v] = adj[u][v] < 0 ? opt : std::min(adj[u][v], opt);
                }
            }
        }
    }

    // Dijkstras
    std::vector<std::vector<std::pair<int,LL>>> adjlist(N+1);
    for (int u = 1; u <= N; ++u) {
        for (int v = u+1; v <= N; ++v) if (u != v && isrepair[u] && isrepair[v] && adj[u][v] >= 0 && adj[u][v] <= D) {
            adjlist[u].push_back({v, adj[u][v]});
            adjlist[v].push_back({u, adj[u][v]});
        }
    }

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push(State(1, 0ll));
    std::vector<bool> visited(N+1, false);
    LL ans = -1;
    while (!pq.empty()) {
        State curr = pq.top(); pq.pop();
        if (curr.v == N) {
            ans = curr.c; break;
        }
        if (visited[curr.v]) continue;
        visited[curr.v] = true;
        for (const std::pair<int,LL> &next : adjlist[curr.v]) {
            pq.push(State(next.first, curr.c + next.second));
        }
    }

    if (ans >= 0) {
        printf("%lld\n", ans);
    } else {
        printf("stuck\n");
    }


    return 0;
}
