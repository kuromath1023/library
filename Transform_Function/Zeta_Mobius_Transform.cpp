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
vector<T> subset_mobius(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (j >> i & 1) {
                a[j] -= a[j ^ (1 << i)];
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
vector<T> superset_mobius(int n, vector<T> a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (!(j >> i & 1)) {
                a[j] -= a[j | (1 << i)];
            }
        }
    }
    return a;
}