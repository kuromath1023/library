template<typename T>
vector<T> dijkstra(const Graph<T> &G, int s = 0) {
    using P = pair<T, int>;
    vector<T> dist(int(G.size()), numeric_limits<T>::max() / T(2));
    dist[s] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, v] = pq.top(); 
        pq.pop();

        if (dist[v] < d) continue;
        for (auto &e : G[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}