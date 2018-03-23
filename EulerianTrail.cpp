#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

//adjancent lists
//destroys g
vector<int> EulerianTrail(const int s, vector<vector<int>> &g, const bool directed) {
        //for (int i = 0; i < g.size(); i ++) sort(g[i].rbegin(), g[i].rend()); //finds the 'minimum' Eulerian trail
        //not proven and not necessarily correct
        function<void (int, vector<int> &)> dfs = [&](int u, vector<int> &trail) {
                while (!g[u].empty()) {
                        int v = g[u].back();
                        g[u].pop_back();
                        if (!directed) {
                                for (int i = 0; i < g[v].size(); i ++) {
                                        if (g[v][i] == u) {
                                                g[v].erase(g[v].begin() + i);
                                                break;
                                        }
                                }
                        }
                        dfs(v, trail);
                }
                trail.push_back(u);
        };
        vector<int> trail;
        dfs(s, trail);
        reverse(trail.begin(), trail.end());
        return trail;
}

//adjacent matrix
//destroys g
vector<int> EulerianTrail(const int s, vector<vector<int>> &g, const bool directed) {
        function<void (int, vector<int> &)> dfs = [&](int u, vector<int> &trail) {
                for (int v = 0; v < g.size(); v ++) if (g[u][v] > 0) {
                        g[u][v] --;
                        if (!directed) g[v][u] --;
                        dfs(v, trail);
                }
                trail.push_back(u);
        };
        vector<int> trail;
        dfs(s, trail);
        reverse(trail.begin(), trail.end());
        return trail;
}

int main() {
        int n, m;
        scanf("%d %d", &n, &m);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i ++) {
                int a, b;
                scanf("%d %d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        vector<int> trail = EulerianTrail(0, g, false);
        for (int v : trail) cerr << v + 1 << ' '; cerr << endl;
        return 0;
}
