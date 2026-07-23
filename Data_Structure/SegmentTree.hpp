#pragma once

template <typename Monoid>
struct SegmentTree {
private:
    using S = typename Monoid::value_type;
    int n, size;
    vector<S> data;

    void init(int n_) {
        n = n_;
        size = 1;
        while (size < n) size <<= 1;
        data.assign(2 * size, Monoid::e());
    }

    template<typename F>
    void build(const F &f) {
        for (int i = 0; i < n; i++) data[i + size] = f(i);
        for (int i = size - 1; i >= 1; i--) data[i] = Monoid::op(data[i << 1], data[i << 1 | 1]);
    }

public:
    SegmentTree(int n) { init(n); }
    SegmentTree(const vector<S> &a) {
        init(int(a.size()));
        build([&](int i) -> S { return a[i]; });
    }
    template<typename F> SegmentTree(int n, const F &f) {
        init(n);
        build(f);
    }

    S get(int k) const { 
        return data[k + size];
    }

    void set(int k, const S &x) {
        k += size;
        data[k] = x;
        while (k >>= 1) {
            data[k] = Monoid::op(data[k << 1], data[k << 1 | 1]);
        }
    }

    S prod(int l, int r) const {
        l += size;
        r += size;
        S vl = Monoid::e(), vr = Monoid::e();
        while (l < r) {
            if (l & 1) vl = Monoid::op(vl, data[l++]);
            if (r & 1) vr = Monoid::op(data[--r], vr);
            l >>= 1, r >>= 1;
        }
        return Monoid::op(vl, vr);
    }

    S all_prod() const {
        return data[1];
    }

    template<typename F> int max_right(int l, const F &f) {
        assert(0 <= l && l <= n);
        assert(f(Monoid::e()));
        if (l == n) return n;
        l += size;
        S sum = Monoid::e();
        do {
            while (!(l & 1)) l >>= 1;
            if (!f(Monoid::op(sum, data[l]))) {
                while (l < size) {
                    l <<= 1;
                    if (f(Monoid::op(sum, data[l]))) {
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

    template<typename F> int min_left(int r, const F &f) {
        assert(0 <= r && r <= n);
        assert(f(Monoid::e()));
        if (r == 0) return 0;
        r += size;
        S sum = Monoid::e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(Monoid::op(data[r], sum))) {
                while (r < size) {
                    r = r << 1 | 1;
                    if (f(Monoid::op(data[r], sum))) {
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
        cout << "--SegmentTree debug--" << '\n';
        for (int i = 0; i < n; i++) cout << get(i) << " \n"[i == n - 1];
    }
};