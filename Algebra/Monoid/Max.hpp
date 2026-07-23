#pragma once

template<typename T, T Id = numeric_limits<T>::lowest()>
struct Monoid_Max {
    using value_type = T;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) { return max(a, b); }
    static constexpr S e() { return Id; }
};