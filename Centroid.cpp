#include <cstdio>
#include <functional>
#include <vector>
#include <iostream>
#include <map>
#include <set>
using namespace std;

vector<int> Centroid(const vector<vector<int>> &g) {
        int n = g.size();
        vector<int> centroid;
        vector<int> sz(n);
        function<void (int, int)> dfs = [&](int u, int prev) {
                sz[u] = 1;
                bool is_centroid = true;
                for (auto v : g[u]) if (v != prev) {
                        dfs(v, u);
                        sz[u] += sz[v];
                        if (sz[v] > n / 2) is_centroid = false;
                }
                if (n - sz[u] > n / 2) is_centroid = false;
                if (is_centroid) centroid.push_back(u);
        };
        dfs(0, -1);
        return centroid;
}

//verified at  
//'https://beta.atcoder.jp/contests/arc087/tasks/arc087_d'
//'https://beta.atcoder.jp/contests/dwacon2018-prelims/tasks/dwacon2018_prelims_e'
vector<int> Centroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
        static vector<int> sz(g.size());
        function<void (int, int)> get_sz = [&](int u, int prev) {
                sz[u] = 1;
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        get_sz(v, u);
                        sz[u] += sz[v];
                }
        };
        get_sz(root, -1);
        int n = sz[root];
        vector<int> centroid;
        function<void (int, int)> dfs = [&](int u, int prev) {
                bool is_centroid = true;
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        dfs(v, u);
                        if (sz[v] > n / 2) is_centroid = false;
                }
                if (n - sz[u] > n / 2) is_centroid = false;
                if (is_centroid) centroid.push_back(u);
        };
        dfs(root, -1);
        return centroid;
}

int main() {
        int n;
        scanf("%d", &n);
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b;
                scanf("%d%d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        vector<bool> dead(n, false);
        vector<int> centroid = Centroid(0, g, dead);
        for (auto c : centroid) cerr << c << endl;
}
