struct edge {
        int to;
        int cost;
        bool operator > (const edge &r) const { return cost > r.cost; }
};
vector<int> Dijkstra(int start, const vector<vector<edge>> &g) {
        int n = g.size();
        vector<int> dist(n, 1 << 30);
        priority_queue<edge, vector<edge>, greater<edge>> q;
        dist[start] = 0;
        q.push({ start, 0 });
        while (!q.empty()) {
                edge now = q.top();
                q.pop();
                for (auto next : g[now.to]) {
                        if (dist[next.to] > dist[now.to] + next.cost) {
                                dist[next.to] = dist[now.to] + next.cost;
                                q.push({ next.to, dist[next.to] });
                        }
                }
        }
        return dist;
}

//unweighted graph
vector<int> Dijkstra(int start, const vector<vector<int>> &g) {
        int n = (int) g.size();
        vector<int> dist(n, 1 << 30);
        priority_queue<pair<int, int>> que;
        dist[start] = 0;
        que.push({0, start});
        while (!que.empty()) {
                auto p = que.top();
                que.pop();
                int u = p.second;
                for (auto v : g[u]) {
                        if (dist[v] > dist[u] + 1) {
                                dist[v] = dist[u] + 1;
                                que.push({-dist[v], v});
                        }
                }
        }
        return dist;
}
