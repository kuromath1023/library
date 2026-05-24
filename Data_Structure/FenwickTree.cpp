template<typename T> 
struct FenwickTree {
    int n;
    vector<T> data;

    FenwickTree(int n_) : n(n_ + 1), data(n, T(0)) {}

    void add(int k, T x) {
        for (k++; k < n; k += k & -k) data[k] += x;
    }

    T sum(int k) {
        T s = 0;
        for (; k > 0; k -= k & -k) s += data[k];
        return s;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    int lower_bound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int k = 1 << __lg(n); k; k >>= 1) {
            if (x + k < n && data[x + k] < w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x;
    }

    int upper_bound(T w) {
        if (w < 0) return 0;
        int x = 0;
        for (int k = 1 << __lg(n); k; k >>= 1) {
            if (x + k < n && data[x + k] <= w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x;
    }
};