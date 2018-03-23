int V;
vector<int> g[101010];
int match[101010];
bool used[101010];
void add_edge(int v, int u) {
        g[v].push_back(u);
        g[u].push_back(v);
}
bool dfs(int v) {
        used[v] = true;
        for (auto u : g[v]) {
                int w = match[u];
                if (w < 0 || (!used[w] && dfs(w))) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                }
        }
        return false;
}
int BipartiteMatching() {
        int res = 0;
        memset(match, -1, sizeof match);
        for (int v = 0; v < V; v ++) {
                if (match[v] < 0) {
                        memset(used, 0, sizeof used);
                        if (dfs(v)) {
                                res ++;
                        }
                }
        }
        return res;
}
