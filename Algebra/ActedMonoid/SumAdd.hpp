#pragma once

#include "library/Algebra/Monoid/Add.hpp"

template<typename T>
struct ActedMonoid_SumAdd {
    using Monoid = Monoid_Add<T>;
    using Operator = Monoid_Add<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        return x + f * T(size);
    }
};