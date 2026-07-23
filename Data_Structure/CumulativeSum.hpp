#pragma once

template<typename T, T(*op)(T, T), T(*e)(), T(*inv)(T), int D>
struct CumulativeSum {
    array<int, D> sz;
    vector<T> data;

    CumulativeSum(const array<int, D> &a) : sz(a) {
        int n = 1;
        for (int i = 0; i < D; i++) {
            sz[i]++;
            n *= sz[i]; 
        }
        data.assign(n, e());
    }

    int id(const array<int, D> &a) const {
        int idx = 0;
        for (int i = 0; i < D; i++) {
            idx = idx * sz[i] + a[i];
        }
        return idx;
    }

    void add(array<int, D> a, T x) {
        for (int i = 0; i < D; i++) a[i]++;
        data[id(a)] = op(data[id(a)], x);
    }

    void build() {
        array<int, D> a;
        for (int d = 0; d < D; d++) {
            fill(a.begin(), a.end(), 0);

            while (true) {
                if (a[d] > 0) {
                    auto b = a;
                    b[d]--;
                    data[id(a)] = op(data[id(a)], data[id(b)]);
                }

                int i = D - 1;
                while (i >= 0) {
                    a[i]++;
                    if (a[i] < sz[i]) break;
                    a[i] = 0;
                    i--;
                }
                if (i < 0) break;
            }
        }
    }

    T get(const array<int, D> &a) const {
        array<int, D> b;
        for (int i = 0; i < D; i++) {
            b[i] = a[i] + 1;
        }
        return sum(a, b);
    }

    T sum(const array<int, D> &L, const array<int, D> &R) const {
        array<int, D> a;
        T s = e();
        for (int bit = 0; bit < (1 << D); bit++) {
            for (int i = 0; i < D; i++) {
                a[i] = bit >> i & 1 ? R[i] : L[i];
            }
            if (__builtin_popcount(bit) & 1) s = op(s, inv(data[id(a)]));
            else s = op(s, data[id(a)]);
        }
        return s;
    } 
};