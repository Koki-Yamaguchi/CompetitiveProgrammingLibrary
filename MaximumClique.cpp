#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int MaximumIndependentSet(int n, const vector<long long> &g) {
        int res = 0;
        function<void (long long, int)> dfs = [&](long long remain, int cnt) {
                for (bool update = true; update; ) {
                        update = false;
                        for (int i = 0; i < n; i ++) if (remain & (1LL << i)) {
                                int deg = __builtin_popcountll(remain & g[i]);
                                if (deg <= 1) {
                                        cnt ++;
                                        remain &= ~((1LL << i) | g[i]);
                                        update = true;
                                }
                        }
                }
                res = max(res, cnt);
                if (remain) {
                        int k = __builtin_ctzll(remain);
                        dfs(remain & ~(1LL << k), cnt);
                        dfs(remain & ~(g[k] | (1LL << k)), cnt + 1);
                }
        };
        dfs((1LL << n) - 1, 0);
        return res;
}
int MaximumClique(const int n, const vector<long long> &g) {
        vector<long long> gg(n);
        for (int i = 0; i < n; i ++) gg[i] = ~g[i];
        return MaximumIndependentSet(n, gg);
}

int main() {
        return 0;
}
