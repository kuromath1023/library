#pragma once

vector<int> z_algorithm(const string &S) {
    vector<int> Z(int(S.size()));
    Z[0] = S.size();
    int i = 1, j = 0;
    while (i < int(S.size())) {
        while (i + j < int(S.size()) && S[j] == S[i + j]) j++;
        Z[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < int(S.size()) && k + Z[k] < j) Z[i + k] = Z[k], k++;
        i += k;
        j -= k;
    }
    return Z;
} 