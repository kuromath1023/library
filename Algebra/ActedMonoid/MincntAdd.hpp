#pragma once

#include <library/Algebra/Monoid/Mincnt.hpp>
#include <library/Algebra/Monoid/Add.hpp>

template<typename T>
struct ActedMonoid_MincntAdd {
    using Monoid = Monoid_Mincnt<T>;
    using Operator = Monoid_Add<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (x.second == 0) return x;
        return {x.first + f, x.second};
    }
};