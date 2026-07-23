#pragma once

template<typename T, T Id = numeric_limits<T>::max()>
struct Monoid_Mincnt {
    using value_type = pair<T, T>;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) {
        if (a.first < b.first) return a;
        if (a.first > b.first) return b;
        return {a.first, a.second + b.second}; 
    }
    static constexpr S e() { return {Id, 0}; }
};