#pragma once

template<typename T, T MinId = numeric_limits<T>::max(), T MaxId = numeric_limits<T>::lowest()>
struct Monoid_MinMax {
    using value_type = pair<T, T>;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) {
        return {min(a.first, b.first), max(a.second, b.second)};
    }
    static constexpr S e() { return {MinId, MaxId}; }
};