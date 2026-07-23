#pragma once

template<uint32_t mod>
struct modint {
    using u32 = uint32_t;
    using u64 = uint64_t;
    static_assert(mod < (u32(1) << 31));
    u32 x;

    static modint raw(u32 val) {
        modint p;
        p.x = val;
        return p;
    }

    constexpr modint() : x(0) {}
    constexpr modint(int val) : x(val >= 0 ? val % mod : (mod - (-val) % mod) % mod) {}
    constexpr modint(int64_t val) : x(val >= 0 ? val % mod : (mod - (-val) % mod) % mod) {}

    modint &operator+=(const modint &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }

    modint &operator-=(const modint &p) {
        if ((x += (mod - p.x)) >= mod) x -= mod;
        return *this;
    }

    modint &operator*=(const modint &p) {
        x = (u32)(1LL * x * p.x % mod);
        return *this;
    }

    modint &operator/=(const modint &p) {
        *this *= p.inv();
        return *this;
    }

    modint operator-() const { return modint::raw(x ? mod - x : u32(0)); }
    modint operator+(const modint &p) const { return modint(*this) += p; }
    modint operator-(const modint &p) const { return modint(*this) -= p; }
    modint operator*(const modint &p) const { return modint(*this) *= p; }
    modint operator/(const modint &p) const { return modint(*this) /= p; }
    bool operator==(const modint &p) const { return x == p.x; }
    bool operator!=(const modint &p) const { return x != p.x; }

    modint pow(int64_t n) const {
        assert(n >= 0);
        modint ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    modint inv() const {
        assert(x != 0);
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b), swap(u -= t * v, v);
        }
        return modint(u);
    }

    u32 val() const {
        return x;
    }

    u32 get_mod() const {
        return mod;
    }

    friend istream &operator>>(istream &is, modint &a) {
        int64_t x;
        is >> x;
        a = modint(x);
        return is;
    }

    friend ostream &operator<<(ostream &os, const modint &a) {
        return os << a.val();
    }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;