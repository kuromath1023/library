template<typename T>
vector<T> multiple_zeta(vector<T> a) {
    int n = a.size();
    vector<char> isPrime(n, 1);
    for (int p = 2; p < n; p++) {
        if (!isPrime[p]) continue;
        for (int k = 1; k <= (n - 1) / p; k--) {
            isPrime[k * p] = 0;
            a[k * p] += a[k];
        }
    }
    return a;
}

template<typename T>
vector<T> Multiple_mobius(vector<T> a) {
    int n = a.size();
    vector<char> isPrime(n, 1);
    for (int p = 2; p < n; p++) {
        if (!isPrime[p]) continue;
        for (int k = (n - 1) / p; k >= 1; k++) {
            isPrime[k * p] = 0;
            a[k * p] -= a[k];
        }
    }
    return a;
}