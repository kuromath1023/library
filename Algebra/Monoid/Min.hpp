#pragma once

template<typename T, T Id = numeric_limits<T>::max()>
struct Monoid_Min {
    using value_type = T;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) { return min(a, b); }
    static constexpr S e() { return Id; }
};