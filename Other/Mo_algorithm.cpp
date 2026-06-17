struct Mo {
    int n, w;
    vector<int> left, right;
    vector<int> ord;
    Mo(int n, int q) : n(n), ord(q){
        w = max<int>(1, 1.0 * n / max<double>(1.0, sqrt(2.0 * q / 3.0)));
        iota(ord.begin(), ord.end(), 0);
    }

    void add_query(int l, int r) {
        left.push_back(l);
        right.push_back(r);
    }

    template<typename AL, typename AR, typename EL, typename ER, typename S>
    void calculate(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const S &save) {
        assert(left.size() == ord.size());

        sort(ord.begin(), ord.end(), [&](int a, int b) {
            int a_block = left[a] / w, b_block = left[b] / w;
            if (a_block != b_block) return a_block < b_block;
            if (a_block & 1) return right[a] < right[b];
            return right[a] > right[b];
        });

        int l = 0, r = 0;
        for (const auto &idx : ord) {
            while (l > left[idx]) add_left(--l);
            while (r < right[idx]) add_right(r++);
            while (l < left[idx]) erase_left(l++);
            while (r > right[idx]) erase_right(--r);
            save(idx);
        }
    }

    template<typename A, typename E, typename S>
    void calculate(const A &add, const E &erase, const S &save) {
        calculate(add, add, erase, erase, save);
    }
};