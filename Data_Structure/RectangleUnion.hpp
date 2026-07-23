#pragma once

#include "library/Data_Structure/LazySegmentTree.hpp"
#include "library/Algebra/ActedMonoid/MincntAdd.hpp"

template<typename T, typename Area>
struct RectangleUnion {
private:
    using S = typename ActedMonoid_MincntAdd<T>::Monoid::value_type;
    struct Rectangle {
        T l, d, r, u;
    };
    vector<Rectangle> rectangles;
public:
    RectangleUnion(int n) {
        rectangles.reserve(n);
    }

    void add(T l, T d, T r, T u) {
        assert(l <= r && d <= u);
        rectangles.push_back(Rectangle{l, d, r, u});
    }

    Area solve() {
        int n = rectangles.size();
        if (n == 0) return 0;

        struct Query {
            T x;
            int idx;
            T type;
        };

        vector<Query> queries;
        vector<T> ys;
        queries.reserve(2 * n), ys.reserve(2 * n);
        for (int i = 0; i < n; i++) {
            auto &rect = rectangles[i];
            queries.push_back(Query{rect.l, i, 1});
            queries.push_back(Query{rect.r, i, -1});
            ys.push_back(rect.d);
            ys.push_back(rect.u);
        }
        sort(queries.begin(), queries.end(), [](Query a, Query b) { return a.x < b.x; });
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        vector<int> L(n), R(n);
        for (int i = 0; i < n; i++) {
            L[i] = lower_bound(ys.begin(), ys.end(), rectangles[i].d) - ys.begin();
            R[i] = lower_bound(ys.begin(), ys.end(), rectangles[i].u) - ys.begin();
        }

        LazySegmentTree<ActedMonoid_MincntAdd<T>> seg(int(ys.size()) - 1, [&](int i) -> S {
            return {0, ys[i + 1] - ys[i]};
        });

        Area ans = 0;
        T total = ys.back() - ys.front();
        for (int i = 0; i + 1 < int(queries.size()); i++) {
            auto &[x, idx, type] = queries[i];
            seg.apply(L[idx], R[idx], type);
            auto [min, cnt] = seg.all_prod();
            T dx = queries[i + 1].x - x;
            T dy = total - (min == 0 ? cnt : 0);
            ans += Area(dx) * Area(dy);
        }
        return ans;
    }
};