#pragma once

template<typename T>
struct Monoid_Affine {
    using value_type = pair<T, T>;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) {
        return {a.first * b.first, a.first * b.second + a.second};
    }
    static constexpr S e() { return {T(1), T(0)}; }
    static constexpr T eval(const S &f, T x) {
        return f.first * x + f.second;
    }
};