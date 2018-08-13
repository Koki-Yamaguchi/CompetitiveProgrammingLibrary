#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

vector<vector<int>> OmniDirectionalTreeDP(const vector<vector<int>> &g) {
        int n = g.size();
        assert(n != 1);
        vector<vector<int>> dp(n);
        vector<int> far(n);
        function<void (int, int)> dfs = [&](int u, int prev) {
                for (auto v : g[u]) if (v != prev) {
                        dfs(v, u);
                        far[u] = max(far[u], far[v] + 1);
                        dp[u].push_back(far[v] + 1);
                }
        };
        dfs(0, -1);
        vector<vector<int>> left(n), right(n);
        auto calc = [&](int u) {
                left[u].resize(g[u].size());
                right[u].resize(g[u].size());
                left[u].front() = dp[u].front(), right[u].back() = dp[u].back();
                for (int i = 0; i < (int) g[u].size() - 1; i ++) left[u][i + 1] = max(left[u][i], dp[u][i + 1]);
                for (int i = (int) g[u].size() - 1; i >= 1; i --) right[u][i - 1] = max(right[u][i], dp[u][i - 1]);
                return;
        };
        calc(0);
        function<void (int, int)> dfs2 = [&](int u, int prev) {
                int idx = 0;
                for (auto v : g[u]) if (v != prev) {
                        int ma = 0;
                        if (idx - 1 >= 0) ma = max(ma, left[u][idx - 1]);
                        if (idx + 1 < (int) right[u].size()) ma = max(ma, right[u][idx + 1]);
                        dp[v].push_back(ma + 1);
                        calc(v);
                        dfs2(v, u);
                        idx ++;
                }
        };
        dfs2(0, -1);
        return dp;
};
