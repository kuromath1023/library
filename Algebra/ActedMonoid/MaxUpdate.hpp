#pragma once

#include <library/Algebra/Monoid/Max.hpp>
#include <library/Algebra/Monoid/Update.hpp>

template<typename T>
struct ActedMonoid_MaxUpdate {
    using Monoid = Monoid_Max<T>;
    using Operator = Monoid_Update<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (!f) return x;
        return f.value();
    }
};