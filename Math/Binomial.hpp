template<typename T>
struct Binomial {
    vector<T> fact_vec, ifact_vec;

    Binomial(int n = 1) : fact_vec(1, T(1)), ifact_vec(1, T(1)) { modify(n); }

    void modify(int n) {
        int m = fact_vec.size();
        if (n < m) return;
        n = max(n, m * 2);
        fact_vec.resize(n + 1);
        ifact_vec.resize(n + 1);
        for (int i = m; i <= n; i++) fact_vec[i] = fact_vec[i - 1] * T(i);
        ifact_vec[n] = T(1) / fact_vec[n];
        for (int i = n - 1; i >= m; i--) ifact_vec[i] = ifact_vec[i + 1] * T(i + 1);
    }

    T fact(int k) {
        if (k < 0) return 0;
        modify(k);
        return fact_vec[k];
    }

    T invfact(int k) {
        if (k < 0) return 0;
        modify(k);
        return ifact_vec[k];
    }

    T inv(int k) {
        if (k < 0) return inv(-k) * T(-1);
        if (k == 0) return 1;
        return fact(k - 1) * invfact(k);
    }

    T P(int n, int r) {
        if (n < 0 || r < 0 || n < r) return 0;
        return fact(n) * invfact(n - r);
    }

    T C(int n, int r) {
        if (n < 0 || r < 0 || n < r) return 0;
        return fact(n) * invfact(r) * invfact(n - r);
    }

    T invC(int n, int r) {
        if (n < 0 || r < 0 || n < r) return 0;
        return fact(r) * fact(n - r) * invfact(n); 
    }
    
    T H(int n, int r) {
        return C(n + r - 1, n);
    }
};