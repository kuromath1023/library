#include "library/Modint/Montgomery_modint.hpp"

namespace fast_factorize {
    using mint = Montgomery_modint;
    using u64 = uint64_t;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    bool MillerRabin(u64 n, const vector<u64> &A) {
        mint::set_mod(n);
        u64 s = 0, d = n - 1;
        while (~d & 1) {
            s++;
            d >>= 1;
        }

        for (u64 a : A) {
            if (n <= a) break;
            mint x = mint(a).pow(d);
            if (x != 1) {
                int t = 0;
                while (t < s) {
                    if (x == n - 1) break;
                    x *= x;
                    t++;
                }
                if (t == s) return false;
            }
        }
        return true;
    }

    bool primetest(u64 n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (~n & 1) return false;
        if (n < 4759123141LL) return MillerRabin(n, {2, 7, 61});
        return MillerRabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    }

    u64 PollardRho(u64 n) {
        if (~n & 1) return 2;
        if (primetest(n)) return n;
        if (mint::get_mod() != n) mint::set_mod(n);
        mint c, unit = 1;
        auto f = [&](mint x) { return x * x + c; };
        auto random = [&](u64 l, u64 r) {
            return uniform_int_distribution<u64>(l, r)(rng);
        };

        while (1) {
            mint x, y, z, q = unit;
            constexpr int m = 128;
            u64 g = 1;
            c = random(1, n - 1);
            y = random(1, n - 1);
            for (int r = 1; g == 1; r <<= 1) {
                x = y;
                for (int i = 0; i < r; i++) y = f(y);
                for (int k = 0; k < r && g == 1; k += m) {
                    z = y;
                    for (int i = 0; i < min(m, r - k); i++) {
                        y = f(y);
                        q *= x - y;
                    }
                    g = gcd(q.val(), n);
                }
            }
            if (g != n) return g;
            do {
                z = f(z);
                g = gcd((x - z).val(), n);
            } while (g == 1);
        }
    }

    vector<u64> inner_factorize(u64 n) {
        if (n <= 1) return {};
        u64 p = PollardRho(n);
        if (p == n) return {p};
        auto l = inner_factorize(p);
        auto r = inner_factorize(n / p);
        l.append_range(r);
        return l;
    }

    vector<u64> factorize(u64 n) {
        auto F = inner_factorize(n);
        sort(F.begin(), F.end());
        return F;
    }

    vector<u64> divisors(u64 n) {
        if (n == 0) return {};
        auto pf = factorize(n);
        vector<pair<u64, int>> F;
        F.reserve(int(pf.size()));
        for (u64 &p : pf) {
            if (F.empty() || F.back().first != p) {
                F.emplace_back(p, 1);
            } else {
                F.back().second++;
            }
        }

        vector<u64> d = {1};
        for (auto &[p, e] : F) {
            int sz = d.size();
            u64 pw = 1;
            for (int i = 0; i < e; i++) {
                pw *= p;
                for (int j = 0; j < sz; j++) {
                    d.push_back(d[j] * pw);
                }
            }
        }
        sort(d.begin(), d.end());
        return d;
    }
};

using fast_factorize::primetest;
using fast_factorize::factorize;
using fast_factorize::divisors;