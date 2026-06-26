template<typename S, S(*op)(S, S), S(*e)(), typename F, S(*mapping)(F, S), F(*composition)(F, F), F(*id)()>
struct LazySegmentTree {
private:
    int n, lg, size;
    vector<S> data;
    vector<F> lazy;

    void init(int n_) {
        n = n_, lg = 0, size = 1;
        while (size < n) size <<= 1, lg++;
        data.assign(2 * size, e());
        lazy.assign(size, id());
    }

    void build(const vector<S> &a) {
        for (int i = 0; i < n; i++) data[i + size] = a[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void update(int k) {
        data[k] = op(data[k << 1], data[k << 1 | 1]);
    }

    void apply_at(int k, const F &f) {
        data[k] = mapping(f, data[k]);
        if (k < size) lazy[k] = composition(f, lazy[k]);
    }

    void push(int k) {
        apply_at(k << 1, lazy[k]);
        apply_at(k << 1 | 1, lazy[k]);
        lazy[k] = id();
    }

public:
    LazySegmentTree(int n) { init(n); }
    LazySegmentTree(const vector<S> &a) { init(int(a.size())); build(a); }

    void set(int k, S x) {
        k += size;
        for (int i = lg; i >= 1; i--) push(k >> i);
        data[k] = x;
        for (int i = 1; i <= lg; i++) update(k >> i);
    }

    S get(int k) {
        k += size;
        for (int i = lg; i >= 1; i--) push(k >> i);
        return data[k];
    }

    void apply(int k, const F &f) {
        k += size;
        for (int i = lg; i >= 1; i--) push(k >> i);
        data[k] = mapping(f, data[k]);
        for (int i = 1; i <= lg; i++) update(k >> i);
    }

    void apply(int l, int r, const F &f) {
        if (l >= r) return;
        l += size;
        r += size;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l2 < r2) {
            if (l2 & 1) apply_at(l2++, f);
            if (r2 & 1) apply_at(--r2, f);
            l2 >>= 1;
            r2 >>= 1; 
        }

        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    S prod(int l, int r) {
        if (l >= r) return e();
        l += size;
        r += size;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S vl = e(), vr = e();
        while (l < r) {
            if (l & 1) vl = op(vl, data[l++]);
            if (r & 1) vr = op(data[--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return op(vl, vr);
    }
};