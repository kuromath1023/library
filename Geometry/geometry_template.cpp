template<typename T>
struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x_, T y_) : x(x_), y(y_) {}

    Point &operator+=(const Point &p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(const Point &p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point operator+(const Point &p) const { return Point(*this) += p; }
    Point operator-(const Point &p) const { return Point(*this) -= p; }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point &p) const { return x != p.x || y != p.y; }
    bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
    Point operator-() const { return Point{-x, -y}; }
    Point operator*(T t) const { return Point{x * t, y * t}; }
    Point operator/(T t) const { return Point{x / t, y / t}; }

    long double abs() const { return sqrtl(x * x + y * y); }
    long double angle() const { return atan2l(y, x); }
    int pos() const {
        if (y > 0) return 1;
        if (y == 0 && 0 <= x) return 0;
        return -1;
    }

    Point rotate(long double theta) {
        static_assert(!is_integral<T>::value);
        long double c = cosl(theta);
        long double s = sinl(theta);
        return Point{ x * c - y * s, x * s + y * c };
    }
};

template<typename T>
T cross(const Point<T> &a, const Point<T> &b) { return a.x * b.y - a.y * b.x; }

template<typename T>
long double dist(const Point<T> &a, const Point<T> &b) {
    T dx = a.x - b.x;
    T dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

template<typename T>
void argument_sort(vector<Point<T>> &v) {
    sort(v.begin(), v.end(), [](Point<T> &a, Point<T> &b) {
        if (a.pos() != b.pos()) return a.pos() < b.pos();
        return cross(a, b) > 0;
    });
}