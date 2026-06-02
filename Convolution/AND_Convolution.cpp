template<typename T>
vector<T> subset_zeta(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (j >> i & 1) {
                a[j] += a[j ^ (1 << i)];
            }
        } 
    }
    return a;
}

template<typename T>
vector<T> superset_zeta(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (!(j >> i & 1)) {
                a[j] += a[j | (1 << i)];
            }
        }
    }
    return a;
}

template<typename T>
vector<T> and_convolution(int n, vector<T> a, vector<T> b) {
    vector<T> za = superset_zeta(n, a);
    vector<T> zb = superset_zeta(n, b);
    vector<T> zc(1 << n);
    for (int i = 0; i < (1 << n); i++) zc[i] = za[i] * zb[i];
    vector<T> c = superset_mobius(n, zc);
    return c;
}