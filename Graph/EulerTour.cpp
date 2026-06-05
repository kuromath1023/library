template<typename Graph>
struct EulerTour {
private:
    using S = pair<int, int>;
    static S op(S a, S b) { return min(a, b); }
    static S e() { return {1 << 30, -1}; }

    struct SparseTable {
        int n;
        vector<vector<S>> table;
        SparseTable() = default;
        SparseTable(const vector<S> &a) { build(a); }

        void build(const vector<S> &a) {
            n = int(a.size());
            table.assign(__lg(n) + 1, vector<S>(n, e()));
            table[0] = a;
            for (int k = 0; k + 1 < int(table.size()); k++) {
                for (int i = 0; i + (1 << (k + 1)) <= n; i++) {
                    table[k + 1][i] = op(table[k][i], table[k][i + (1 << k)]); 
                }
            }
        }

        S prod(int l, int r) const {
            int k = __lg(r - l);
            return op(table[k][l], table[k][r - (1 << k)]);
        }
    };


    void build() {
        in.assign(int(G.size()), -1);
        out.assign(int(G.size()), -1);
        int idx = 0;
        dfs(root, -1, idx, 0);
        sparse.build(a);
    }

    void dfs(int v, int p, int &idx, int depth) {
        in[v] = idx;
        a[idx++] = {depth, v};
        for (auto &e : G[v]) {
            if (e.to == p) continue;
            dfs(e.to, v, idx, depth + 1);
            a[idx++] = {depth, v};
        }
        out[v] = idx;
    }

public:
    Graph &G;
    int root;
    vector<int> in, out;
    vector<S> a;
    SparseTable sparse;
    EulerTour(Graph &G, int root = 0) : G(G), root(root), a(2 * int(G.size()) - 1) { build(); }

    int lca(int u, int v) {
        if (in[u] > in[v]) swap(u, v);
        return sparse.prod(in[u], in[v] + 1).second;
    }

    pair<int, int> idx(int v) {
        return {in[v], out[v]};
    }

    template<typename F>
    void path_query(int u, int v, bool vertex, const F &f) {
        int l = lca(u, v);
        f(in[l] + 1, in[u] + 1);
        if (vertex) f(in[l], in[l] + 1);
        f(in[l] + 1, in[v] + 1);
    }

    template<typename F>
    void subtree_query(int v, bool vertex, const F &f) {
        f(in[v] + (!vertex), out[v]);
    }
};