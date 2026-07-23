struct UnionFind {
    vector<int> par, size;
    
    UnionFind(int n) : par(n), size(n, 1) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int root(int x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    bool merge(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);

        size[x] += size[y];
        par[y] = x;
        return true;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    } 

    vector<vector<int>> groups() {
        vector<vector<int>> member(int(par.size())), res;
        for (int i = 0; i < int(par.size()); i++) member[root(i)].push_back(i);
        for (int i = 0; i < int(par.size()); i++) if (!member[i].empty()) res.push_back(member[i]);
        return res;
    }
};