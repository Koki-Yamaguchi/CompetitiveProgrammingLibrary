struct edge {
        int to, cap, rev;
};
bool used[101010];
vector<edge> g[101010];
static const int INF = 0x3f3f3f3f;
void add_edge(int from, int to, int cap) {
        g[from].push_back((edge) { to, cap, (int)g[to].size() });
        g[to].push_back((edge) { from, 0, (int)g[from].size() - 1 });
}
int dfs(int v, int t, int f) {
        if (v == t) return f;
        used[v] = true;
        for (int i = 0; i < g[v].size(); i ++) {
                edge& e = g[v][i];
                if (!used[e.to] && e.cap > 0) {
                        int d = dfs(e.to, t, min(f, e.cap));
                        if (d > 0) {
                                e.cap -= d;
                                g[e.to][e.rev].cap += d;
                                return d;
                        }
                }
        }
        return 0;
}
int MaxFlow(int s, int t) {
        int flow = 0;
        while (true) {
                memset(used, false, sizeof(used));
                int f = dfs(s, t, INF);
                if (f == 0) return flow;
                flow += f;
        }
}
