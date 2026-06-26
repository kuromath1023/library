template<typename T, typename S, S(*op)(S, S), S(*e)(), typename F, S(*mapping)(F, S, T), F(*composition)(F, F), F(*id)()>
struct DynamicLazySegmentTree {
private:
    struct Node {
        S val;
        F lazy;
        T len;
        Node *l, *r;
        Node() : val(e()), lazy(id()), l(nullptr), r(nullptr) {}
        Node(T len) : val(e()), lazy(id()), len(len), l(nullptr), r(nullptr) {}
    };

    T n;
    Node *root;

    void apply_at(Node *node, const F &f) {
        node->val = mapping(f, node->val, node->len);
        node->lazy = composition(f, node->lazy);
    }

    void push(Node *node, T l, T r) {
        if (node->lazy == id() || r - l == 1) return;
        T m = (l + r) >> 1;
        if (!node->l) node->l = new Node(m - l);
        if (!node->r) node->r = new Node(r - m);

        apply_at(node->l, node->lazy);
        apply_at(node->r, node->lazy);
        node->lazy = id();
    }

    void update(Node *node) {
        node->val = op((node->l ? node->l->val : e()), (node->r ? node->r->val : e())); 
    }

    void set(Node *&node, const T &k, const S &x, T l, T r) {
        if (!node) node = new Node(r - l);
        if (r - l == 1) {
            node->val = x;
            node->lazy = id();
            return;
        }
        push(node, l, r);
        T m = (l + r) >> 1;
        if (k < m) set(node->l, k, x, l, m);
        else set(node->r, k, x, m, r);
        update(node);
    }

    S get(Node *node, const T &k, T l, T r) {
        while (r - l > 1) {
            if (!node) return e();
            push(node, l, r);
            T m = (l + r) >> 1;
            if (k < m) {
                r = m;
                node = node->l;
            } else {
                l = m;
                node = node->r;
            }
        }
        return node ? node->val : e();
    }

    void apply(Node *&node, const F &f, T a, T b, T l, T r) {
        if (r <= a || b <= l) return;
        if (!node) node = new Node(r - l);
        if (a <= l && r <= b) {
            apply_at(node, f);
            return;
        }
        push(node, l, r);
        T m = (l + r) >> 1;
        apply(node->l, f, a, b, l, m);
        apply(node->r, f, a, b, m, r);
        update(node);
    }

    S prod(Node *node, T a, T b, T l, T r) {
        if (!node || r <= a || b <= l) return e();
        if (a <= l && r <= b) return node->val;
        push(node, l, r);
        T m = (l + r) >> 1;
        S vl = prod(node->l, a, b, l, m);
        S vr = prod(node->r, a, b, m, r);
        return op(vl, vr);
    }

public:
    DynamicLazySegmentTree(T n) : n(n), root(nullptr) {}

    void set(const T &k, const S &x) {
        set(root, k, x, 0, n);
    }

    S get(const T &k) {
        return get(root, k, 0, n);
    }

    void apply(T l, T r, const F &f) {
        apply(root, f, l, r, 0, n);
    }

    S prod(T l, T r) {
        return prod(root, l, r, 0, n);
    }
};