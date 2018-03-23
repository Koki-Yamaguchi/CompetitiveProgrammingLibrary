#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>
using namespace std;

//usagi's
struct heavy_light_decomposition_t {
    int n; // |V'|
    vector<int> a; // V ->> V' epic
    vector<vector<int> > path; // V' -> V*, bottom to top order, disjoint union of codomain matchs V
    vector<map<int,int> > pfind; // V' * V -> int, find in path
    vector<int> parent; // V' -> V
    heavy_light_decomposition_t(int v, vector<vector<int> > const & g) {
        n = 0;
        a.resize(g.size());
        dfs(v, -1, g);
    }
    int dfs(int v, int p, vector<vector<int> > const & g) {
        int heavy_node = -1;
        int heavy_size = 0;
        int desc_size = 1;
        for (int w : g[v]) if (w != p) {
            int size = dfs(w, v, g);
            desc_size += size;
            if (heavy_size < size) {
                heavy_node = w;
                heavy_size = size;
            }
        }
        if (heavy_node == -1) {
            a[v] = n;
            n += 1;
            path.emplace_back();
            path.back().push_back(v);
            pfind.emplace_back();
            pfind.back()[v] = 0;
            parent.push_back(p);
        } else {
            int i = a[heavy_node];
            a[v] = i;
            pfind[i][v] = path[i].size();
            path[i].push_back(v);
            parent[i] = p;
        }
        return desc_size;
    }
};

int main() {
        int n;
        scanf("%d", &n);
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b;
                scanf("%d %d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        heavy_light_decomposition_t hld(n, g);
        return 0;
}
