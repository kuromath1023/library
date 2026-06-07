template<typename T, typename S, S(*op)(S, S), S(*e)()>
struct DynamicSegmentTree {
private:
    struct Node {
        S val;
        Node *l, *r;
        Node() : val(e()), l(nullptr), r(nullptr) {}
        Node(S val) : val(val), l(nullptr), r(nullptr) {}
    };

    void set(Node *&node, const T &k, const S &x, T l, T r) {
        if (!node) node = new Node(x);
        if (r - l == 1) {
            node->val = x;
            return;
        }
        T m = (l + r) >> 1;
        if (k < m) set(node->l, k, x, l, m);
        else set(node->r, k, x, m, r);
        node->val = e();
        if (node->l) node->val = op(node->val, node->l->val);
        if (node->r) node->val = op(node->val, node->r->val);
    }

    S get(const T &k, T l, T r) const {
        Node *node = root;
        while (r - l > 1) {
            if (!node) return e();
            T m = (l + r) >> 1LL;
            if (k < m) {
                r = m;
                node = node->l;
            } else {
                l = m;
                node = node->r;
            }
        }
        return node->val;
    }

    S prod(Node *node, T a, T b, T l, T r) const {
        if (!node || r <= a || b <= l) return e();
        if (a <= l && r <= b) return node->val;
        T m = (l + r) >> 1;
        S vl = prod(node->l, a, b, l, m);
        S vr = prod(node->r, a, b, m, r);
        return op(vl, vr);
    }

public:
    T n;
    Node *root;
    DynamicSegmentTree(T n) : n(n), root(nullptr) {}

    void set(const T &k, const S &x) {
        set(root, k, x, 0, n);
    }

    S get(const T &k) const {
        return get(k, 0, n);
    }

    S prod(T l, T r) const {
        return prod(root, l, r, 0, n);
    }
};