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

template<typename T>
struct WaveletMatrix {
    using u32 = uint32_t;
    using u64 = uint64_t;
    u32 n, lg;
    vector<T> v;
    vector<SuccinctBitVector> bv;
    vector<u32> mid;

    WaveletMatrix(int n_) : n(n_), v(n_, T()) { }  
    WaveletMatrix(const vector<T> &a) : n(int(a.size())), v(a) { build(); }  

    void set(int i, const T &x) {
        v[i] = x;
    }

    void build() {
        lg = __lg(max<T>(*max_element(v.begin(), v.end()), T(n)) + 1) + 1;
        bv.assign(lg, SuccinctBitVector(n));
        mid.assign(lg);
        vector<T> l(n), r(n);
        for (int h = lg - 1; h >= 0; h--) {
            u32 left = 0, right = 0;
            for (int i = 0; i < n; i++) {
                if (v[i] >> h & 1) {
                    bv[h].set(i);
                    r[right++] = v[i];
                }   else {
                    l[left++] = v[i];
                }
            }
            bv[h].build();
            mid[h] = left;
            v.swap(l);
            for (int i = 0; i < right; i++) v[left + i] = r[i];
        }
    }

    void succ(u32 &l, u32 &r, bool f, u32 h) {
        l = bv[h].rank(f, l) + f * mid[h]; 
        r = bv[h].rank(f, r) + f * mid[h];
    }

    T access(u32 k) {
        T ret = 0;
        for (int h = lg - 1; h >= 0; h--) {
            if (bv[h].access(k)) {
                ret |= (1ULL << h);
                k = mid[h] + bv[h].rank(1, k);
            }
            else k = bv[h].rank(0, k);
        }
        return ret;
    }

    u32 rank(T x, u32 r) {
        u32 l = 0;
        for (int h = lg - 1; h >= 0; h--) {
            succ(l, r, x >> h & 1, h);
        }
        return r - l;
    }

    u32 rank(T x, u32 l, u32 r) {
        return rank(x, r) - rank(x, l);
    }

    T kth_smallest(u32 l, u32 r, u32 k) {
        T ret = 0;
        for (int h = lg - 1; h >= 0; h--) {
            u32 l0 = bv[h].rank(0, l);
            u32 r0 = bv[h].rank(0, r);
            bool f = (k >= r0 - l0);
            if (f) {
                k -= r0 - l0;
                ret |= (1ULL << h);
            }
            succ(l, r, f, h);
        }
        return ret;
    }

    T kth_largest(u32 l, u32 r, u32 k) {
        return kth_smallest(l, r, r - l - 1 - k);
    }

    u32 range_freq(u32 l, u32 r, T upper) {
        u32 ret = 0;
        for (int h = lg - 1; h >= 0; h--) {
            bool f = (upper >> h & 1);
            if (f) ret += bv[h].rank(0, r) - bv[h].rank(0, l);
            succ(l, r, f, h);
        }
        return ret;
    }

    u32 range_freq(u32 l, u32 r, T lower, T upper) {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    T prev_value(u32 l, u32 r, T upper) {
        u32 cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }

    T next_value(u32 l, u32 r, T lower) {
        u32 cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt); 
    }
};