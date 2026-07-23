#pragma once

template<typename ActedMonoid>
struct LazySegmentTree {
private:
    using Monoid = typename ActedMonoid::Monoid;
    using Operator = typename ActedMonoid::Operator;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    int n, lg, size;
    vector<S> data;
    vector<F> lazy;

    void init(int n_) {
        n = n_, lg = 0, size = 1;
        while (size < n) size <<= 1, lg++;
        data.assign(2 * size, Monoid::e());
        lazy.assign(size, Operator::e());
    }

    template<typename G>
    void build(const G &g) {
        for (int i = 0; i < n; i++) data[i + size] = g(i);
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void update(int k) {
        data[k] = Monoid::op(data[k << 1], data[k << 1 | 1]);
    }

    int length(int k) const {
        return 1 << (lg - __lg(k));
    }

    void apply_at(int k, const F &f) { 
        data[k] = ActedMonoid::act(f, data[k], length(k));
        if (k < size) lazy[k] = Operator::op(f, lazy[k]);
    }

    void push(int k) {
        apply_at(k << 1, lazy[k]);
        apply_at(k << 1 | 1, lazy[k]);
        lazy[k] = Operator::e();
    }

public:
    LazySegmentTree(int n) { init(n); }
    LazySegmentTree(const vector<S> &a) {
        init(int(a.size())); 
        build([&](int i) -> S { return a[i]; }); 
    }
    template<typename G> LazySegmentTree(int n, const G &g) {
        init(n);
        build(g);
    }

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
        data[k] = ActedMonoid::act(f, data[k], 1);
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
        if (l >= r) return Monoid::e();
        l += size;
        r += size;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S vl = Monoid::e(), vr = Monoid::e();
        while (l < r) {
            if (l & 1) vl = Monoid::op(vl, data[l++]);
            if (r & 1) vr = Monoid::op(data[--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return Monoid::op(vl, vr);
    }

    S all_prod() const {
        return data[1];
    }

    template<typename C>
    int max_right(int l, const C &check) {
        assert(0 <= l && l <= n);
        assert(check(Monoid::e()));
        if (l == n) return n;
        l += size;
        for (int i = lg; i >= 1; i--) push(l >> i);
        S sum = Monoid::e();
        do {
            while (!(l & 1)) l >>= 1;
            if (!check(Monoid::op(sum, data[l]))) {
                while (l < size) {
                    push(l);
                    l <<= 1;
                    if (check(Monoid::op(sum, data[l]))) {
                        sum = Monoid::op(sum, data[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sum = Monoid::op(sum, data[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template<typename C>
    int min_left(int r, const C &check) {
        assert(0 <= r && r <= n);
        assert(check(Monoid::e()));
        if (r == 0) return 0;
        r += size;
        for (int i = lg; i >= 1; i--) push((r - 1) >> i);
        S sum = Monoid::e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!check(Monoid::op(data[r], sum))) {
                while (r < size) {
                    push(r);
                    r = r << 1 | 1;
                    if (check(Monoid::op(data[r], sum))) {
                        sum = Monoid::op(data[r], sum);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sum = Monoid::op(data[r], sum);
        } while ((r & -r) != r);
        return 0;
    }

    void dump() {
        cout << "--LazySegmentTree debug--" << '\n';
        for (int i = 0; i < n; i++) cout << get(i) << " \n"[i == n - 1];
    }
};