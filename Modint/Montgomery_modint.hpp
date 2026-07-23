#pragma once

struct Montgomery_modint {
    using modint = Montgomery_modint;
    using i64 = int64_t;
    using u64 = uint64_t;
    using u128 = __uint128_t;

    u64 x;
    static inline u64 mod;
    static inline u64 r;
    static inline u64 R2;

    Montgomery_modint() : x(u64(0)) {}
    Montgomery_modint(const int64_t &val) : x(reduce(u128(val % mod + mod) * R2)) {}

    static u64 get_r() {
        u64 ret = mod;
        for (int i = 0; i < 5; i++) ret *= 2 - mod * ret;
        return ret;
    }

    static void set_mod(u64 m) {
        assert(m & 1);
        assert(m < (u64(1) << 62));
        mod = m;
        r = get_r();
        R2 = -u128(mod) % mod;
    }

    static u64 reduce(const u128 &T) {
        return (T + u128(u64(T) * u64(-r)) * mod) >> 64;
    }

    modint &operator+=(const modint &p) {
        if (i64(x += p.x - 2 * mod) < 0) x += 2 * mod;
        return *this;
    }

    modint &operator-=(const modint &p) {
        if (i64(x -= p.x) < 0) x += 2 * mod;
        return *this;
    }

    modint &operator*=(const modint &p) {
        x = reduce(u128(x) * p.x);
        return *this;
    }

    modint &operator/=(const modint &p) {
        *this *= p.inv();
        return *this;
    }

    modint operator-() const { return modint() - *this; }
    modint operator+(const modint &p) const { return modint(*this) += p; }
    modint operator-(const modint &p) const { return modint(*this) -= p; }
    modint operator*(const modint &p) const { return modint(*this) *= p; }
    modint operator/(const modint &p) const { return modint(*this) /= p; }
    bool operator==(const modint &p) const { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); }
    bool operator!=(const modint &p) const { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x); }

    modint pow(u64 n) const {
        modint ret(1), mul(*this);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    modint inv() const {
        assert(x != 0);
        return pow(mod - 2);
    }

    u64 val() const {
        u64 ret = reduce(u128(x));
        return ret >= mod ? ret - mod : ret;
    }

    static u64 get_mod() {
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