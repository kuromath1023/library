#pragma once

#include <library/Algebra/Monoid/Add.hpp>
#include <library/Algebra/Monoid/Update.hpp>

template<typename T>
struct ActedMonoid_SumUpdate {
    using Monoid = Monoid_Add<T>;
    using Operator = Monoid_Update<T>;
    using S = typename Monoid::value_type;
    using F = typename Operator::value_type;
    static constexpr S act(const F &f, const S &x, const int &size) {
        if (!f) return x;
        return f.value() * T(size);
    }
};