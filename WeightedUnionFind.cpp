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

struct WeightedUnionFind {
        int n;
        vector<pair<int, int>> parent; // (node, weight)
        WeightedUnionFind(int x) {
                n = x;
                parent.resize(n);
                for (int i = 0; i < n; i ++) parent[i] = make_pair(i, 0);
        }
        pair<int, int> find(int x) {
                if (parent[x].first == x) return parent[x];
                auto res = find(parent[x].first);
                return parent[x] = make_pair(res.first, parent[x].second + res.second);
        }
        bool same(int x, int y) {
                return find(x).first == find(y).first;
        }
        void unite(int x, int y, int val) {
                auto u = find(x);
                auto v = find(y);
                if (u.first == v.first) return;
                parent[u.first] = make_pair(v.first, v.second - u.second + val);
        }
        int diff(int x, int y) {
                return parent[x].second - parent[y].second;
        }
};

int main() {
        int n, m;
        scanf("%d %d", &n, &m);
        WeightedUnionFind wuf(n);
        for (int i = 0; i < m; i ++) {
                int l, r, d;
                scanf("%d %d %d", &l, &r, &d);
                l --, r --;
                if (wuf.same(l, r)) {
                        if (wuf.diff(l, r) != d) {
                                puts("No");
                                return 0;
                        }
                } else {
                        wuf.unite(l, r, d);
                }
        }
        puts("Yes");
        return 0;
}
