#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Potentialized_UnionFind {
    vector<int> par, siz;
    vector<T> diff_potential;
    
    Potentialized_UnionFind(int n, T x = 0) : par(n), siz(n, 1), diff_potential(n, x) {
        iota(par.begin(), par.end(), 0);
    } 

    int root(int x) {
        if (par[x] == x) return x;
        int r = root(par[x]);
        diff_potential[x] += diff_potential[par[x]]; 
        return par[x] = r;
    }

    T potential(int k) {
        root(k);
        return diff_potential[k];
    }

    T diff(int x, int y) {
        return potential(y) - potential(x);
    }

    bool merge(int x, int y, T p) {
        p += potential(x) - potential(y);
        x = root(x), y = root(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y), p = -p; 

        siz[x] += siz[y];
        par[y] = x;
        diff_potential[y] = p;
        return true;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int size(int x) {
        return siz[root(x)];
    }
};

int main() { return 0; }