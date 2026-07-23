#pragma once

template<typename T>
struct BIT2D {
    int H, W;
    vector<vector<T>> data;

    BIT2D(int H_, int W_) { init(H_, W_); }

    void init(int H_, int W_) {
        H = H_ + 1;
        W = W_ + 1;
        data.assign(H, vector<T>(W, 0));
    }

    void add(int x, int y, T w) {
        x++, y++;
        for (int i = x; i < H; i += i & -i) {
            for (int j = y; j < W; j += j & -j) {
                data[i][j] += w;
            }
        }
    }

    T sum(int x, int y) {
        T s = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                s += data[i][j];
            }
        }

        return s;
    }

    T sum(int x1, int y1, int x2, int y2) {
        if (x1 >= x2 || y1 >= y2) return T(0);
        return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}