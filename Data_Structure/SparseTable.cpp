template<typename S, S (*op)(S, S), S (*e)()>
struct SparseTable {
    int n;
    vector<vector<S>> table;
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
        if (l >= r) return e();
        int k = __lg(r - l);
        return op(table[k][l], table[k][r - (1 << k)]);
    }
};