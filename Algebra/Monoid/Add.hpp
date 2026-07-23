#pragma once

template<typename T>
struct Monoid_Add {
    using value_type = T;
    using S = T;
    static constexpr S op(const S &a, const S &b) { return a + b; }
    static constexpr S e() { return T(0); }
    static constexpr S inv(const S &x) { return -x; } 
};