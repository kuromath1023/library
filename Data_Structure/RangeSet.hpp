#pragma once

//半開区間　T は int or long long
template<typename T>
struct RangeSet {
    set<pair<T, T>> s;
    vector<pair<T, T>> add;
    T TINF;

    RangeSet() {
        TINF = numeric_limits<T>::max() / 2;
        s.emplace(TINF, TINF);
        s.emplace(-TINF, -TINF);
    }

    bool covered(T l, T r) {
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        return it->first <= l && r <= it->second;
    }

    bool covered(T x) {return covered(x, x + 1);}

    pair<T, T> covered_by(T l, T r) {
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        if (it->first <= l && r <= it->second) return *it;
        return make_pair(-TINF, -TINF);
    }

    pair<T, T> covered_by(T x) {return covered_by(x, x + 1);}

    void insert(T l, T r) {
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        if (it->first <= l && r <= it->second) return;
        while (it->second < l) it++;

        while (it != s.begin() && it != s.end() && it->first <= r) {
            l = min(l, it->first);
            r = max(r, it->second);
            it = s.erase(it);
        }

        s.emplace(l, r);
    } 

    void insert(T x) {
        insert(x, x + 1);
    }

    void erase(T l, T r) {
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        while (it->second < l) it++;
        
        while (it != s.end() && it->first < r) {
            if (it->first < l) add.emplace_back(it->first, l);
            if (r < it->second) add.emplace_back(r, it->second);
            it = s.erase(it); 
        }

        for (auto &p : add) s.emplace(p);
        add.clear();
    }

    void erase(T x) {
        erase(x, x + 1);
    }

    T mex(T x = 0) {
        auto it = prev(s.lower_bound(make_pair(x + 1, x + 1)));
        if (it->first <= x && x < it->second) return it->second;
        else return x;
    }

    int size() {return int(s.size()) - 2;}

    void output() {
        cout << "------This is output------" << endl;
        for (auto [l, r] : s) {
            if (abs(l) == TINF) continue;
            cout << "[" << l << "," << r << ")" << endl;
        }
    }
};

int main() {
    RangeSet<int> s;
    s.insert(0, 5);    // [0, 5)
    s.insert(10, 15);  // [0, 5), [10, 15)
    s.insert(3, 8);    // [0, 8), [10, 15)
    s.erase(4, 12);    // [0, 4), [12, 15)

    cout << s.covered(1, 3) << endl; // true
    auto p = s.covered_by(1, 3);
    cout << p.first << " " << p.second << endl; //[0, 4)
    cout << s.mex() << endl; // 4
    cout << s.size() << endl; // 2
    s.output();

    return 0;
}