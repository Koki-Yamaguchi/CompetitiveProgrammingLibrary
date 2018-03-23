#include "bits/stdc++.h"
using namespace std;

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
                                return  d;
                        }
                }
        }
        return 0;
}

int MaxFlow(int s, int t) {
        int flow = 0;
        while (true) {
                memset(used, 0, sizeof(used));
                int f = dfs(s, t, INF);
                if (f == 0) return flow;
                flow += f;
        }
}

int main() {
        int n, m;
        cin >> n >> m;
        int under = 0;
        for (int i = 0; i < m; i ++) {
                int a, b, x, y;
                cin >> a >> b >> x >> y;
                a --, b --;
                add_edge(a, b, y - x);
                add_edge(a, n + 1, x);
                add_edge(n, b, x);
                if (a == 0) under += x;
        }
        MaxFlow(n, n + 1);
        MaxFlow(n, n - 1);
        MaxFlow(0, n + 1);
        bool can = true;
        for (int i = 0; i < g[n].size(); i ++) {
                edge e = g[n][i];
                if (e.cap != 0) can = false;
        }
        for (int i = 0; i < g[n + 1].size(); i ++) {
                edge e = g[n + 1][i];
                if (g[e.to][e.rev].cap != 0) can = false;
        }
        if (!can) cout << "Impossible" << endl;
        else {
                MaxFlow(0, n - 1);
                int ans = 0;
                for (int i = 0; i < g[0].size(); i ++) {
                        edge e = g[0][i];
                        if (e.to != n + 1) ans += g[e.to][e.rev].cap; 
                }
                cout << ans + under << endl;
        }
        return 0;
}
