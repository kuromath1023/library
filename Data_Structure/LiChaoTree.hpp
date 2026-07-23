#pragma once

template<typename T, T INF>
struct LiChaoTree {
private:
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
        inline T f(T x) const { return a * x + b; }
        inline bool over(const Line &other, const T &x) const {
            return f(x) < other.f(x);
        }
    };

    int size;
    vector<Line> data;
    vector<T> xs;
    void add_line(Line L, int l, int r, int k) {
        while (true) {
            int m = (l + r) >> 1;
            bool left_over = L.over(data[k], xs[l]);
            bool right_over = L.over(data[k], xs[r - 1]);
            if (left_over == right_over) {
                if (left_over) swap(data[k], L);
                return;
            }
            bool mid_over = L.over(data[k], xs[m]);
            if (mid_over) swap(data[k], L);
            if (left_over != mid_over) {
                k = (k << 1), r = m;
            } else {
                k = (k << 1) | 1, l = m;
            }
        }
    }

    void add_line(T a, T b, int k) {
        int h = __bit_width(k) - 1;
        int l = (1 << h) * (k - (1 << h));
        int r = l + (1 << h);
        return add_line(a, b, l, r, k);
    }

public:
    void add_point(const T x) {
        xs.emplace_back(x);
    }

    void build() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        if (xs.size() == 0) xs.emplace_back(0);
        size = 1;
        while (size < int(xs.size())) size <<= 1;
        while (int(xs.size()) < size) xs.push_back(xs.back() + 1); 
        data.assign(2 * size, Line(0, INF));
    }

    void add_line(T a, T b) {
        add_line(Line(a, b), 0, size, 1);
    }

    void add_segment(T a, T b, T l, T r) {
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) add_line(a, b, l++);
            if (r & 1) add_line(a, b, --r);
            l >>= 1;
            r >>= 1;
        }
    }

    T query_id(int k) {
        const T x = xs[k];
        k += size;
        T ret = data[k].f(x);
        while (k > 1) {
            k >>= 1;
            ret = min(ret, data[k].f(x));
        }
        return ret;
    }

    T query(const T &x) {
        int k = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        return query_id(k);
    }
};