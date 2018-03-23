struct edge {
        int to, cap, cost, rev;
};
int V;
vector<edge> g[101010];
int dist[101010];
int prevv[101010];
int preve[101010];
void add_edge(int from, int to, int cap, int cost) {
        g[from].push_back((edge) { to, cap, cost, (int)g[to].size() });
        g[to].push_back((edge) { from, 0, -cost, (int)g[from].size() - 1 });
}
int MinCostFlow(int s, int t, int f) {
        int res = 0;
        while (f > 0) {
                fill(dist, dist + V, INF);
                dist[s] = 0;
                bool update = true;
                while (update) {
                        update = false;
                        for (int v = 0; v < V; v ++) {
                                if (dist[v] == INF) continue;
                                for (int i = 0; i < g[v].size(); i ++) {
                                        edge &e = g[v][i];
                                        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                                                dist[e.to] = dist[v] + e.cost;
                                                prevv[e.to] = v;
                                                preve[e.to] = i;
                                                update = true;
                                        }
                                }
                        }
                }
                if (dist[t] == INF) return -1;
                int d = f;
                for (int v = t; v != s; v = prevv[v]) {
                        d = min(d, g[prevv[v]][preve[v]].cap);
                }
                f -= d;
                res += d * dist[t];
                for (int v = t; v != s; v = prevv[v]) {
                        edge &e = g[prevv[v]][preve[v]];
                        e.cap -= d;
                        g[v][e.rev].cap += d;
                }
        }
        return res;
}
