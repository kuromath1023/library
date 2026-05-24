struct SuccinctBitVector {
    using u64 = uint64_t;
    using u32 = uint32_t;
    vector<u64> block;
    vector<u32> count;

    SuccinctBitVector() = default;
    SuccinctBitVector(int n) { init(n); }
    
    void init(int n) {
        block.resize((n >> 6) + 1, u64(0));
        count.resize(int(block.size()), u32(0));
    }

    void set(int i) {
        block[i >> 6] |= (1ULL << (i & 63));    
    }

    void build() {
        for (int i = 0; i < int(block.size()) - 1; i++) count[i + 1] = count[i] +  __builtin_popcountll(block[i]);
    }

    u32 access(int k) const {
        return (block[k >> 6] >> (k & 63)) & 1ULL;  
    }

    u32 rank(bool f, int k) const {
        u32 s = count[k >> 6] + __builtin_popcountll(block[k >> 6] & ((1ULL << (k & 63)) - 1)); 
        return (f ? s : k - s);
    }
};

template<typename S, typename T>
struct WaveletMatrix {
    using u64 = uint64_t;
    using u32 = uint32_t;
    using P = pair<S, S>;
    
struct FenwickTree {
    u32 n;
    vector<T> data;

    FenwickTree() = default;
    FenwickTree(u32 n_) : n(n_ + 1), data(n_ + 1, T(0)) {}

    void add(u32 k, T x) {
        for (k++; k < n; k += k & -k) data[k] += x;
    }

    T sum(u32 k) const {
        T s = 0;
        for (; k > 0; k -= k & -k) s += data[k];
        return s;
    }

    T sum(u32 l, u32 r) const {
        return sum(r) - sum(l);
    }
};

    int n, lg;
    vector<SuccinctBitVector> bv;
    vector<FenwickTree> fw;
    vector<P> points;
    vector<S> ys;
    vector<u32> mid;

    void add_point(S x, S y) {
        points.emplace_back(x, y);
        ys.emplace_back(y);
    }

    void build() {
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        n = points.size();
        lg = __lg(max(n, 1)) + 1;
        bv.assign(lg, SuccinctBitVector(n));
        fw.assign(lg, FenwickTree(n));
        mid.assign(lg, u32(0));
        vector<u32> C(n), l(n), r(n);
        for (int i = 0; i < n; i++) C[i] = y_id(points[i].second);
        for (int h = lg - 1; h >= 0; h--) {
            int left = 0, right = 0;
            for (int i = 0; i < n; i++) {
                if (C[i] >> h & 1) {
                    bv[h].set(i);
                    r[right++] = C[i];
                } else {
                    l[left++] = C[i];
                }
            }
            bv[h].build();
            mid[h] = left;
            C.swap(l);
            for (int i = 0; i < right; i++) C[left + i] = r[i];
        }
    }

    void succ(u32 &l, u32 &r, bool f, u32 h) {
        l = bv[h].rank(f, l) + f * mid[h]; 
        r = bv[h].rank(f, r) + f * mid[h];
    }

    u32 x_id(S x) const { return lower_bound(points.begin(), points.end(), P{x, -1}) - points.begin(); }
    u32 y_id(S y) const { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); }

    void add(S x, S y, T w) {
        u32 i = lower_bound(points.begin(), points.end(), P{x, y}) - points.begin();
        for (int h = lg - 1; h >= 0; h--) {
            bool f = bv[h].access(i);
            i = bv[h].rank(f, i) + f * mid[h];
            fw[h].add(i, w);
        }
    }

    T _sum(u32 l, u32 r, S upper) {
        T s = 0;
        for (int h = lg - 1; h >= 0; h--) {
            bool f = (upper >> h) & 1;
            if (f) s += fw[h].sum(bv[h].rank(0, l), bv[h].rank(0, r));
            succ(l, r, f, h);
        }
        return s;
    }

    T sum(S L, S D, S R, S U) {
        u32 l = x_id(L), r = x_id(R);
        return _sum(l, r, y_id(U)) - _sum(l, r, y_id(D)); 
    }
};