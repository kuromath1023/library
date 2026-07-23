template<typename Graph>
struct HeavyLightDecomposition {
private:
    void build() {
        size.assign(int(G.size()), 0);
        par.assign(int(G.size()), -1);
        depth.assign(int(G.size()), 0);
        in.assign(int(G.size()), -1);
        out.assign(int(G.size()), -1);
        rev.assign(int(G.size()), -1);
        head.assign(int(G.size()), -1);
        head[root] = root;
        dfs_sz(root, -1);
        int idx = 0;
        dfs_hld(root, idx);
    }

    void dfs_sz(int v, int p) {
        size[v] = 1;
        if (G[v].size() && p == G[v][0].to) swap(G[v][0], G[v].back());
        for (auto &e : G[v]) {
            if (e.to == p) continue;
            par[e.to] = v;
            depth[e.to] = depth[v] + 1;
            dfs_sz(e.to, v);
            size[v] += size[e.to];
            if (size[e.to] > size[G[v][0].to]) {
                swap(e, G[v][0]);
            }
        }
    }

    void dfs_hld(int v, int &idx) {
        in[v] = idx++;
        rev[in[v]] = v; 
        for (auto &e : G[v]) {
            if (e.to == par[v]) continue;
            head[e.to] = (e.to == G[v][0].to ? head[v] : e.to);
            dfs_hld(e.to, idx);
        }
        out[v] = idx;
    }

public:
    Graph &G;
    int root;
    vector<int> size, par, depth, in, out, rev, head;
    HeavyLightDecomposition(Graph &G, int root = 0) : G(G), root(root) { build(); }
    
    int idx(int v) { return in[v]; }

    int la(int v, int d) {
        while (depth[head[v]] > d) v = par[head[v]];
        return rev[in[v] - depth[v] + d];
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (in[u] < in[v]) swap(u, v);
            u = par[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

    vector<pair<int, int>> ascend(int u, int v) {
        vector<pair<int, int>> ret;
        while (head[u] != head[v]) {
            ret.emplace_back(in[u], in[head[u]]);
            u = par[head[u]];
        }
        if (u != v) ret.emplace_back(in[u], in[v] + 1);
        return ret;
    }

    vector<pair<int, int>> descend(int u, int v) {
        if (u == v) return {};
        if (head[u] == head[v]) return {{in[u] + 1, in[v]}};
        vector<pair<int, int>> ret = descend(u, par[head[v]]);
        ret.emplace_back(in[head[v]], in[v]);
        return ret;
    }

    template<typename F>
    void path_query(int u, int v, bool vertex, const F &f) {
        int l = lca(u, v);
        for (auto &[a, b] : ascend(u, l)) f(b, a + 1);
        if (vertex) f(in[l], in[l] + 1);
        for (auto &[a, b] : descend(l, v)) f(a, b + 1);
    }

    template<typename F> 
    void path_noncommutative_query(int u, int v, bool vertex, const F &f) {    
        int l = lca(u, v);
        for (auto &[a, b] : ascend(u, l)) f(a + 1, b);
        if (vertex) f(in[l], in[l] + 1);
        for (auto &[a, b] : descend(l, v)) f(a, b + 1);
    }

    template<typename F>
    void subtree_query(int v, bool vertex, const F &f) {
        f(in[v] + (!vertex), out[v]);
    }
};