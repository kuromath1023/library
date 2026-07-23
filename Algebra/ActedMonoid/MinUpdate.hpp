#pragma once

#include <library/Algebra/Monoid/Min.hpp>
#include <library/Algebra/Monoid/Update.hpp>

template<typename T>
struct ActedMonoid_MinUpdate {
    using Monoid = Monoid_Min<T>;
    using Operator = Monoid_Update<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (!f) return x;
        return f.value();
    }
};