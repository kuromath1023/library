template<int char_size = 26, char base = 'a'>
struct Trie {
    struct Node {
        int c;
        int common;
        int par;
        array<int, char_size> next;
        vector<int> accept;
        Node(int c) : c(c), common(0), par(-1) {
            fill(next.begin(), next.end(), -1);
        }
    };

    int root;
    vector<Node> G;
    Trie(int root = 0) : root(root) {
        G.emplace_back(Node(root));
    }

    void insert(const string &S, const int idx) {
        int pos = root;
        G[pos].common++;
        for (int i = 0; i < int(S.size()); i++) {
            int c = S[i] - base;
            int &next_pos = G[pos].next[c];
            if (next_pos == -1) {
                next_pos = int(G.size());
                G.emplace_back(Node(c));
            }
            G[next_pos].par = pos;
            G[next_pos].common++;
            pos = next_pos;
        }
        G[pos].accept.emplace_back(idx);
    }

    void insert(const string &S) {
        insert(S, G[root].common);
    }

    int find(const string &S) const {
        int pos = root;
        for (int i = 0; i < int(S.size()); i++) {
            int c = S[i] - base;
            if (G[pos].next[c] == -1) return -1;
            pos = G[pos].next[c];
        }
        return pos;
    }

    int count() const { return G[root].common; }
    int size() const { return G.size(); }
};