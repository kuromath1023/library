#pragma once

template<typename T>
struct Matrix {
    vector<vector<T>> A;

    Matrix() = default;
    Matrix(int n, int m) : A(n, vector<T>(m, T())) {}
    Matrix(int n) : A(n, vector<T>(n, T())) {}

    int H() const { return A.size(); }
    int W() const { return A[0].size(); }
    inline const vector<T> &operator[](int k) const { return A[k]; }
    inline vector<T> &operator[](int k) { return A[k]; }

    static Matrix I(int n) {
        Matrix Mat(n);
        for (int i = 0; i < n; i++) Mat[i][i] = 1;
        return (Mat);
    }

    Matrix &operator+=(const Matrix &B) {
        int n = H(), m = W();
        assert(n == B.H() && m == B.W());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] += B[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator-=(const Matrix &B) {
        int n = H(), m = W();
        assert(n == B.H() && m == B.W());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator*=(const Matrix &B) {
        int n = H(), m = B.W(), p = W();
        assert(p == B.H());
        vector<vector<T>> C(n, vector<T>(m, T()));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) {
                for (int j = 0; j < m; j++) {
                    C[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        A.swap(C);
        return (*this);
    }

    Matrix &operator^=(long long k) {
        Matrix B = Matrix::I(H());
        while (k > 0) {
            if (k & 1) B *= (*this);
            (*this) *= (*this);
            k >>= 1LL;
        }
        A.swap(B.A);
        return (*this);
    }


    Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
    Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
    Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }
    Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }
};