#pragma once

#include "library/Algebra/Monoid/Add.hpp"
#include "library/Algebra/Monoid/Affine.hpp"

template<typename T>
struct ActedMonoid_SumAffine {
    using Monoid = Monoid_Add<T>;
    using Operator = Monoid_Affine<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        return f.first * x + f.second * T(size);
    }
};