template<typename T>
struct ReRooting {
    struct Edge {
        int to, idx;
        Edge(int to, int idx) : to(to), idx(idx) {} 
    };
    
    using F1 = function<T(T, T)>;
    using F2 = function<T(T, int)>;
    vector<vector<Edge>> G;
    vector<T> memo, dp;
    const F1 merge;
    const F2 put_vertex;
    const F2 put_edge;
    const T ident;

    ReRooting(int n, const F1 &merge, const F2 &put_vertex, const F2 &put_edge, const T &ident)
        : G(n), memo(n, ident), dp(n), merge(merge), put_vertex(put_vertex), put_edge(put_edge), ident(ident) {}

    void add_edge(int u, int v, int idx) {
        G[u].emplace_back(v, idx);
        G[v].emplace_back(u, idx);
    }

    void build() {
        dfs1(0, -1);
        dfs2(0, -1, ident);
    }

    void dfs1(int v, int par) {
        for (auto &[to, idx] : G[v]) {
            if (to == par) continue;
            dfs1(to, v);
            memo[v] = merge(memo[v], put_edge(memo[to], idx));
        }
        memo[v] = put_vertex(memo[v], v);
    };

    void dfs2(int v, int par, T pval) {
        int deg = G[v].size();
        vector<T> buf(deg);
        for (int i = 0; i < deg; i++) {
            auto &[to, idx] = G[v][i];
            if (to == par) buf[i] = pval;
            else buf[i] = put_edge(memo[to], idx);
        }

        vector<T> ldp(deg + 1, ident), rdp(deg + 1, ident);
        for (int i = 0; i < deg; i++) ldp[i + 1] = merge(ldp[i], buf[i]);
        for (int i = deg - 1; i >= 0; i--) rdp[i] = merge(rdp[i + 1], buf[i]);
        dp[v] = put_vertex(ldp[deg], v);

        for (int i = 0; i < deg; i++) {
            auto &[to, idx] = G[v][i];
            if (to == par) continue;
            dfs2(to, v, put_edge(put_vertex(merge(ldp[i], rdp[i + 1]), v), idx)); 
        }
    };

    const vector<T>& reroot() {
        build();
        return dp;
    }
};