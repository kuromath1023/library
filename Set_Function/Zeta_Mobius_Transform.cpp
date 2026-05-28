template<typename T>
vector<T> subset_zeta(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int T = 0; T < (1 << n); T++) {
            if (T >> i & 1) {
                a[T] += a[T ^ (1 << i)];
            }
        } 
    }
    return a;
}

template<typename T>
vector<T> subset_mobius(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int T = 0; T < (1 << n); T++) {
            if (T >> i & 1) {
                a[T] -= a[T ^ (1 << i)];
            }
        }
    }
    return a;
}

template<typename T>
vector<T> superset_zeta(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int T = 0; T < (1 << n); T++) {
            if (!(T >> i & 1)) {
                a[T] += a[T | (1 << i)];
            }
        }
    }
    return a;
}

template<typename T>
vector<T> superset_mobius(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int T = 0; T < (1 << n); T++) {
            if (!(T >> i & 1)) {
                a[T] -= a[T | (1 << i)];
            }
        }
    }
    return a;
}