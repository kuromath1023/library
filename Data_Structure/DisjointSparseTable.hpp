#pragma once

template<typename S, S(*op)(S, S)>
struct DisjointSparseTable {
    int n;
    vector<vector<S>> table;

    DisjointSparseTable(const vector<S> &v) : n(int(v.size())) {
        int lg = 0;
        while ((1 << lg) < n) lg++;
        table.assign(lg, vector<S>(n));
        table[0] = v;
        for (int k = 1; k < lg; k++) {
            int len = 1 << k;
            for (int i = 0; i < n; i += (len << 1)) {
                int mid = min(i + len, n);
                int r = min(i + (len << 1), n);

                table[k][mid - 1] = v[mid - 1];
                for (int j = mid - 2; j >= i; j--) {
                    table[k][j] = op(v[j], table[k][j + 1]);
                }

                if (n <= mid) break;
                table[k][mid] = v[mid];
                for (int j = mid + 1; j < r; j++) {
                    table[k][j] = op(table[k][j - 1], v[j]);
                }
            }
        }
    }

    S prod(int l, int r) {
        r--;
        if (l == r) return table[0][l];
        int k = 31 - __builtin_clz(l ^ r);
        return op(table[k][l], table[k][r]);
    }
};

