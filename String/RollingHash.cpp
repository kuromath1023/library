struct RollingHash {
private:
    using u64 = unsigned long long;
    static constexpr u64 MASK30 = (1ULL << 30) - 1;
    static constexpr u64 MASK31 = (1ULL << 31) - 1;
    static constexpr u64 MASK61 = (1ULL << 61) - 1;
    static constexpr u64 MOD = MASK61;
    static constexpr u64 adjust = MOD << 2ULL;

    static inline u64 generate_base() {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<u64> dist(1ULL << 30, 1ULL << 60);
        return dist(rng) | 1ULL;
    }
    
    static inline u64 Mul(u64 a, u64 b) {
        u64 p = a >> 31ULL;
        u64 q = a & MASK31;
        u64 r = b >> 31ULL;
        u64 s = b & MASK31;
        u64 x = q * r + p * s;
        u64 t = x >> 30ULL;
        u64 u = x & MASK30;
        return ((p * r) << 1ULL) + t + (u << 31ULL) + q * s;
    }

    static inline u64 CalcMod(u64 x) {
        u64 res = (x >> 61) + (x & MASK61);
        if (res >= MOD) return res - MOD;
        return res;
    }

    static inline u64 base = generate_base();
    static inline vector<u64> power = {1ULL};
    vector<u64> hash = {0ULL};

    static void extend_power(int n) {
        int m = power.size();
        if (n < m) return;
        power.resize(n + 1);
        for (int i = m; i <= n; i++) power[i] = CalcMod(Mul(power[i - 1], base));
    }

    void extend_base(const char &c) {
        hash.emplace_back(CalcMod(Mul(hash.back(), base) + u64(c)));
    }

    void init(const string &S) {
        extend_power(int(S.size()));
        for (char c : S) extend_base(c);
    }

public:
    RollingHash() = default;
    RollingHash(const string &S) {
        init(S);
    }

    u64 get(int k) const {
        return get(0, k);
    }

    u64 get(int l, int r) const {
        return CalcMod(hash[r] - CalcMod(Mul(hash[l], power[r - l]) + adjust));
    }

    static u64 connect(u64 h1, u64 h2, int h2_len) {
        extend_power(h2_len);
        return CalcMod(Mul(h1, power[h2_len]) + h2);
    }

    int lcp(const RollingHash &other) const {
        return lcp(0, (*this).size(), other, 0, other.size());
    }

    int lcp(int l1, int r1, const RollingHash &other, int l2, int r2) const {
        int l = 0;
        int r = min(r1 - l1, r2 - l2) + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (get(l1, l1 + m) == other.get(l2, l2 + m)) l = m;
            else r = m;
        }
        return l;
    }

    int size() const {
        return int(hash.size()) - 1;
    }
};