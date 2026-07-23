#pragma once

template<typename T>
struct Monoid_Gcd {
    using value_type = T;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) { return gcd(a, b); }
    static constexpr S e() { return T(0); }
};