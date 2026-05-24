template<typename T> 
struct FenwickTree {
    int n;
    vector<T> data;

    FenwickTree(int n_) { init(n_); }
    
    void init(int n_) {
        n = n_ + 1;
        data.assign(n, 0);
    }

    void add(int k, T x) {
        for (k++; k < n; k += k & -k) data[k] += x;
    }

    T sum(int k) {
        T s = 0;
        for (; k > 0; k -= k & -k) s += data[k];
        return s;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    int lower_bound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int k = 1 << __lg(n); k; k >>= 1) {
            if (x + k < n && data[x + k] < w) {
                w -= data[x + k];
                x += k;
            }
        }

        return x;
    }

    int upper_bound(T w) {
        if (w < 0) return 0;
        int x = 0;
        for (int k = 1 << __lg(n); k; k >>= 1) {
            if (x + k < n && data[x + k] <= w) {
                w -= data[x + k];
                x += k;
            }
        }

        return x;
    }
};

template<typename S, typename T>
struct StaticPointAddRectangleSum {
    struct Point {
        S x, y;
        T w;
    };

    struct Query {
        S l, d, r, u;
    };

    vector<Point> Points;
    vector<Query> Queries;
    StaticPointAddRectangleSum() = default;
    StaticPointAddRectangleSum(int n, int q) {
        Points.reserve(n);
        Queries.reserve(q);
    }

    void add_point(S x, S y, T w) {
        Points.emplace_back(Point{x, y, w});
    }

    void add_query(S l, S d, S r, S u) {
        Queries.emplace_back(Query{l, d, r, u});
    }

    vector<T> solve() {
        int N = Points.size();
        int Q = Queries.size();
        vector<S> ys;
        for (Point &p : Points) ys.emplace_back(p.y);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        ys.shrink_to_fit();

        struct Event {
            T x;
            int d, u;
            bool type;
            int idx;
        };

        vector<Event> Events;
        for (int i = 0; i < Q; i++) {
            Point &q = Queries[i];
            int d = lower_bound(ys.begin(), ys.end(), q.d) - ys.begin();
            int u = lower_bound(ys.begin(), ys.end(), q.u) - ys.begin();
            Events.emplace_back(Event{q.l, d, u, false, i});
            Events.emplace_back(Event{q.r, d, u, true, i});
        }

        sort(Points.begin(), Points.end(), [](Point &a, Point &b) { return a.x < b.x; });
        sort(Events.begin(), Events.end(), [](Event &a, Event &b) { return a.x < b.x; });

        FenwickTree<T> fw(int(ys.size()));
        vector<T> ans(Q, T(0));
        int j = 0;
        for (Event &E : Events) {
            while (j < N && Points[j].x < E.x) {
                int y = lower_bound(ys.begin(), ys.end(), Points[j].y) - ys.begin();
                fw.add(y, Points[j].w);
                j++;
            }
            ans[E.idx] += fw.sum(E.d, E.u) * (E.type ? 1 : -1);
        }
        return ans;
    }
};