#pragma once

#include <library/Algebra/Monoid/Min.hpp>
#include <library/Algebra/Monoid/Add.hpp>

template<typename T>
struct ActedMonoid_AddMin {
    using Monoid = Monoid_Min<T>;
    using Operator = Monoid_Add<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (x == Monoid::e()) return x;
        return x + f;
    }
};