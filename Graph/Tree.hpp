#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Tree {
private:
    using Graph = vector<vector<int>>;
    Graph G;
    int root;
    vector<array<int, 24>> doubling; 
    vector<int> dep;

    void init() {
        int n = G.size();
        dep.resize(n);
        doubling.resize(n);
        for (auto &v : doubling) fill(v.begin(), v.end(), -1);
        dfs(root, -1, 0);
    }

    void dfs(int v, int par, int d) {
        dep[v] = d;
        for (int u = par, x = 0; u != -1;) {
            doubling[v][x] = u;
            u = doubling[u][x];
            x++;
        }

        for (int &next_v : G[v]) {
            if (next_v == par) continue;
            dfs(next_v, v, d + 1);
        }
    }

public:
    Tree(Graph G_, int root_ = 0) : G(G_), root(root_) {init();}

    int depth(int v) {
        return dep[v];
    }

    int par(int v) {
        return (v == root ? -1 : doubling[v][0]);
    }

    int kth_ancestor(int v, int k) {
        if (k == 0) return v;
        if (dep[v] < k) return -1;
        for (int i = 0; i <= __lg(k); i++) if (k >> i & 1) v = doubling[v][i];
        return v;
    }

    int LCA(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        v = kth_ancestor(v, dep[v] - dep[u]);
        if (u == v) return u;
        for (int i = __lg(dep[u]); i >= 0; i--) {
            if (doubling[u][i] != doubling[v][i]) {
                u = doubling[u][i];
                v = doubling[v][i];
            }
        }
        return doubling[u][0]; 
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
    }

    bool is_on_path(int u, int v, int x) {
        return dist(u, v) == dist(u, x) + dist(x, v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> G(N);
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        G[i].push_back(p);
        G[p].push_back(i);
    }

    Tree T(G);
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << T.LCA(u, v) << '\n';
    }
}