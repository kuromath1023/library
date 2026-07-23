#pragma once

template<typename T>
struct Monoid_Update {
    using value_type = optional<T>;
    using S = value_type;
    static constexpr S op(const S &a, const S &b) { return b.has_value() ? b : a; }
    static constexpr S e() { return nullopt; }
};