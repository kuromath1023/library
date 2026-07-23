#pragma once

#include <library/Algebra/Monoid/Max.hpp>
#include <library/Algebra/Monoid/Add.hpp>

template<typename T>
struct ActedMonoid_AddMax {
    using Monoid = Monoid_Max<T>;
    using Operator = Monoid_Add<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (x == Monoid::e()) return x;
        return x + f;
    }
};