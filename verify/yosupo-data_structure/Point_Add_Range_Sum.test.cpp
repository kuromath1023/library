#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "FenwickTree.hpp"

void solve() {
    int N, Q;
    cin >> N >> Q;
    FenwickTree<ll> fw(N);
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        fw.add(i, a);
    }

    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, x;
            cin >> p >> x;
            fw.add(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << fw.sum(l, r) << '\n';
        }
    }
}

int main() {
    cincout();
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}