template <typename S, S(*op)(S, S), S(*e)()>
struct SegmentTree {
    int n, size;
    vector<S> data;

    SegmentTree(int n_) { init(n_); }
    SegmentTree(const vector<S> &a) { init(int(a.size())); build(a); } 

    void init(int n_) {
        n = n_;
        size = 1;
        while (size < n) size <<= 1;
        data.assign(2 * size, e());
    }

    void build(const vector<S> &a) {
        for (int i = 0; i < n; i++) data[i + size] = a[i];
        for (int i = size - 1; i >= 1; i--) data[i] = op(data[i << 1], data[i << 1 | 1]);
    }

    S get(int k) { return data[k + size]; }

    void set(int k, S x) {
        k += size;
        data[k] = x;
        while (k >>= 1) {
            data[k] = op(data[k << 1], data[k << 1 | 1]);
        }
    }

    S prod(int l, int r) {
        l += size;
        r += size;
        S vl = e(), vr = e();
        while (l < r) {
            if (l & 1) vl = op(vl, data[l++]);
            if (r & 1) vr = op(data[--r], vr);
            l >>= 1, r >>= 1;
        }
        return op(vl, vr);
    }

    template<typename F> int max_right(int l, const F &f) {
        if (l == n) return n;
        assert(f(e()));
        l += size;
        S sum = e();
        do {
            while (!(l & 1)) l >>= 1;
            if (!f(op(sum, data[l]))) {
                while (l < size) {
                    l <<= 1;
                    if (f(op(sum, data[l]))) {
                        sum = op(sum, data[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sum = op(sum, data[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template<typename F> int min_left(int r, const F &f) {
        if (r == 0) return 0;
        assert(f(e()));
        r += size;
        S sum = e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(data[r], sum))) {
                while (r < size) {
                    r = r << 1 | 1;
                    if (f(op(data[r], sum))) {
                        sum = op(data[r], sum);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sum = op(data[r], sum);
        } while ((r & -r) != r);
        return 0;
    }
};