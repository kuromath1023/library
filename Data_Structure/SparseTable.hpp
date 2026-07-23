#pragma once

template<typename Monoid>
struct SparseTable {
    using S = typename Monoid::value_type;
    int n;
    vector<vector<S>> table;
    SparseTable(const vector<S> &a) { build(a); }

    void build(const vector<S> &a) {
        n = int(a.size());
        table.assign(__lg(n) + 1, vector<S>(n, Monoid::e()));
        table[0] = a;
        for (int k = 0; k + 1 < int(table.size()); k++) {
            for (int i = 0; i + (1 << (k + 1)) <= n; i++) {
                table[k + 1][i] = Monoid::op(table[k][i], table[k][i + (1 << k)]); 
            }
        }
    }

    S prod(int l, int r) const {
        if (l >= r) return Monoid::e();
        int k = __lg(r - l);
        return Monoid::op(table[k][l], table[k][r - (1 << k)]);
    }
};