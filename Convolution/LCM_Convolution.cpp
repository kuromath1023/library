template<typename T>
vector<T> multiple_zeta(vector<T> a) {
    int n = a.size();
    vector<char> isPrime(n, 1);
    for (int p = 2; p < n; p++) {
        if (!isPrime[p]) continue;
        for (int k = 1; k <= (n - 1) / p; k++) {
            isPrime[k * p] = 0;
            a[k * p] += a[k];
        }
    }
    return a;
}

template<typename T>
vector<T> multiple_mobius(vector<T> a) {
    int n = a.size();
    vector<char> isPrime(n, 1);
    for (int p = 2; p < n; p++) {
        if (!isPrime[p]) continue;
        for (int k = (n - 1) / p; k >= 1; k--) {
            isPrime[k * p] = 0;
            a[k * p] -= a[k];
        }
    }
    return a;
}

template<typename T>
vector<T> lcm_convolution(vector<T> a, vector<T> b) {
    int n = a.size();
    vector<T> za = multiple_zeta(a);
    vector<T> zb = multiple_zeta(b);
    vector<T> zc(n);
    for (int i = 1; i < n; i++) zc[i] = za[i] * zb[i];
    vector<T> c = multiple_mobius(zc);
    return c;
}