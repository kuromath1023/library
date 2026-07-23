#pragma once

template<int char_size, char base>
struct AhoCorasick {
    struct Node {
        int par, fail;
        array<int, char_size> next;
        vector<int> accept;
        Node() : par(-1), fail(-1) {
            next.fill(-1);
        }
    };

    vector<Node> G;
    int root;
    int idx;

    AhoCorasick() : root(0), idx(0) {
        G.emplace_back(Node());
    }

    void insert(const string &S) {
        int pos = root;
        for (int i = 0; i < int(S.size()); i++) {
            int c = S[i] - base;
            int next_pos = G[pos].next[c];
            if (next_pos == -1) {
                next_pos = int(G.size());
                G.push_back(Node());
                G[pos].next[c] = next_pos;
                G[next_pos].par = pos;
            }
            pos = next_pos;
        }
        G[pos].accept.push_back(idx);
        idx++;
    }

    void build() {
        queue<int> q;

        for (int c = 0; c < char_size; c++) {
            int &next_pos = G[root].next[c];
            if (next_pos != -1) {
                G[next_pos].fail = 0;
                q.push(next_pos);
            } else {
                next_pos = 0;
            }
        }

        while (!q.empty()) {
            int pos = q.front();
            q.pop();
            for (int c = 0; c < char_size; c++) {
                int &next_pos = G[pos].next[c];
                if (next_pos != -1) {
                    G[next_pos].fail = G[G[pos].fail].next[c];
                    auto &fail_accept = G[G[next_pos].fail].accept;
                    G[next_pos].accept.insert(G[next_pos].accept.end(), fail_accept.begin(), fail_accept.end());
                    q.push(next_pos);
                } else {
                    G[pos].next[c] = G[G[pos].fail].next[c];
                }
            }
        }
    }

    int move(int pos, char c) const {
        return G[pos].next[c - base];
    }

    int move(int pos, int c) const {
        return G[pos].next[c];
    }

    int size() const {
        return G.size();
    }

    const Node& operator[](int v) const { return G[v]; }
    Node& operator[](int v) { return G[v]; }
};