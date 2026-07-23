#pragma once

template<typename Graph>
vector<int> Cycle_Detection(const Graph &G, bool is_directed) {
    int N = G.size();
    vector<int> cycle;
    vector<int> state(N, 0);
    vector<int> pre_edge(N, -1), pre_vertex(N, -1);

    auto reconstruct = [&](int s, int t) {
        cycle.emplace_back(pre_edge[t]);
        for (; t != s; t = pre_vertex[t]) {
            cycle.emplace_back(pre_edge[t]);
        }
        reverse(cycle.begin(), cycle.end());
    };

    auto dfs = [&](auto dfs, int v, int pe) -> bool {
        state[v] = 1;
        
        for (auto &e : G[v]) {
            if (!is_directed && e.idx == pe) continue;

            if (state[e.to] == 0) {
                pre_edge[e.to] = e.idx;
                pre_vertex[e.to] = v;
                if (dfs(dfs, e.to, e.idx)) return true;
            }


            else if (state[e.to] == 1) {
                reconstruct(v, e.to);
                return true;
            }
        }

        state[v] = 2;
        return false;
    };

    for (int i = 0; i < N; i++) {
        if (state[i] != 0) continue;
        if (dfs(dfs, i, -1)) {
            return cycle;
        }
    }
    return {};
}