template<typename T>
void warshall_floyd(vector<vector<T>> &dist) {
    if (int(dist.size()) == 0) return;
    int N = dist.size();
    for (int i = 0; i < N; i++) dist[i][i] = 0;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}