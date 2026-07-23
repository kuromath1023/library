template<typename Graph>
vector<int> topological_sort(const Graph &G) {
    int n = G.size();
    vector<int> ans, in(n);
    queue<int> q;
    for (int i = 0; i < n; i++) for (auto &e: G[i]) in[e.to]++;
    for (int i = 0; i < n; i++) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ans.push_back(v);
        for (auto &e : G[v]) {
            if (--in[e.to] == 0) q.push(e.to);
        }
    }
    if (int(ans.size()) != n) return {};
    return ans;
}