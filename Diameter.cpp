//Verified by "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A"

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;

#define unittest_name_helper(counter) unittest_ ## counter
#define unittest_name(counter) unittest_name_helper(counter)
#define unittest __attribute__((constructor)) void unittest_name(__COUNTER__) ()

struct edge { int to, cost; };
int Diameter(int n, const vector<vector<edge>> &g) {
        vector<int> dp(n), sz(n);
        function<void (int, int)> dfs = [&](int u, int prev) {
                vector<int> child;
                for (auto e : g[u]) {
                        int v = e.to, d = e.cost;
                        if (v == prev) continue;
                        dfs(v, u);
                        child.push_back(sz[v] + d);
                        sz[u] = max(sz[u], sz[v] + d);
                        dp[u] = max(dp[u], dp[v]);
                }
                sort(child.rbegin(), child.rend());
                if (child.size() >= 1) dp[u] = max(dp[u], child[0]);
                if (child.size() >= 2) dp[u] = max(dp[u], child[0] + child[1]);
        };
        dfs(0, -1);
        return dp[0];
}

unittest {
        int n = 11;
        vector<vector<edge>> g(n);
        g[0].push_back({1, 9});
        g[1].push_back({0, 9});
        g[0].push_back({2, 1});
        g[2].push_back({0, 1});
        g[1].push_back({8, 4});
        g[8].push_back({1, 4});
        g[2].push_back({3, 3});
        g[3].push_back({2, 3});
        g[2].push_back({4, 7});
        g[4].push_back({2, 7});
        g[8].push_back({10, 2});
        g[10].push_back({8, 2});
        g[8].push_back({9, 7});
        g[9].push_back({8, 7});
        g[3].push_back({5, 5});
        g[5].push_back({3, 5});
        g[5].push_back({7, 3});
        g[7].push_back({5, 3});
        g[5].push_back({6, 8});
        g[6].push_back({5, 8});
        assert(Diameter(n, g) == 37);
}

int main() {
        return 0;
}
