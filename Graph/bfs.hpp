#pragma once

template<typename T>
vector<T> dfs(const Graph<T> &G, int s) {
    vector<T> dist(int(G.size()), T(-1));
    dist[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto &e : G[v]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[v] + 1;
                q.push(e.to);
            }
        }
    }
    return dist;
}