template<typename T>
struct Edge {
    int from, to;
    T cost;
    int idx;
    Edge() = default;
    Edge(int from_, int to_, T cost_ = 1, int idx_ = -1) 
        : from(from_), to(to_), cost(cost_), idx(idx_) {}
};  

template<typename T>
struct Graph {
    vector<vector<Edge<T>>> G;
    int idx;

    Graph() = default;
    explicit Graph(int n) : G(n), idx(0) {}

    void add_edge(int u, int v, T cost = 1) {
        G[u].emplace_back(u, v, cost, idx);
        G[v].emplace_back(v, u, cost, idx++);
    }

    void add_directed_edge(int u, int v, T cost = 1) {
        G[u].emplace_back(u, v, cost, idx++);
    }

    void read(int M, bool weighted = false, bool directed = false, bool is_1origin = true) {
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            if (is_1origin) u--, v--;
            T w = 1;
            if (weighted) cin >> w;
            if (directed) {
                add_directed_edge(u, v, w);
            } else {
                add_edge(u, v, w);
            }
        }
    }

    int size() const { return G.size(); }
    vector<Edge<T>> &operator[](int v) { return G[v]; }
    const vector<Edge<T>> &operator[](int v) const { return G[v]; }
};