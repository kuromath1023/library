template<typename T, T INF>
struct DynamicLiChaoTree {
private:
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
        Line() : a(0), b(INF) {}
        inline T f(T x) const { return a * x + b; }
        inline bool over(const Line &other, const T &x) const {
            return f(x) < other.f(x);
        }
    };

    struct Node {
        Line L;
        Node *l, *r;
        Node() : L(), l(nullptr), r(nullptr) {}
        Node (const Line &L) : L(L), l(nullptr), r(nullptr) {}
    };

    Node* add_line(Node *node, Line L, T l, T r) {
        if (!node) return node = new Node(L);
        T m = (l + r) >> 1;
        bool left_over = L.over(node->L, l);
        bool right_over = L.over(node->L, r - 1);
        if (left_over == right_over) {
            if (left_over) swap(node->L, L);
            return node;
        }
        bool mid_over = L.over(node->L, m);
        if (mid_over) swap(node->L, L);
        if (left_over != mid_over) {
            node->l = add_line(node->l, L, l, m);
        } else {
            node->r = add_line(node->r, L, m, r);
        }
        return node;
    }

    Node* add_segment(Node *node, Line L, T a, T b, T l, T r) {
        if (r <= a || b <= l) return node;
        if (a <= l && r <= b) {
            node = add_line(node, L, l, r);
            return node;
        }
        if (!node) node = new Node();
        T m = (l + r) >> 1;
        node->l = add_segment(node->l, L, a, b, l, m);
        node->r = add_segment(node->r, L, a, b, m, r);
        return node;
    }

    T query(T x, T l, T r) {
        Node *node = root;
        T ret = INF;
        while (l < r && node) {
            ret = min(ret, node->L.f(x));
            T m = (l + r) >> 1;
            if (x < m) {
                r = m;
                node = node->l;
            } else {
                l = m;
                node = node->r;
            }
        }
        return ret;
    }

public:
    Node *root;
    T xmin, xmax;
    DynamicLiChaoTree(T xmin, T xmax) : root(nullptr), xmin(xmin), xmax(xmax) {}

    void add_line(T a, T b) {
        root = add_line(root, Line(a, b), xmin, xmax + 1);
    }

    void add_segment(T a, T b, T l, T r) {
        root = add_segment(root, Line(a, b), l, r, xmin, xmax + 1);
    }

    T query(const T x) {
        return query(x, xmin, xmax + 1);
    }
};