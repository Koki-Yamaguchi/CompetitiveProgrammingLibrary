vector<edge> e;
struct edge {
        int a, b, cost;
};
bool comp(const edge& e1, const edge& e2) {
        return e1.cost < e2.cost;
}
sort(e.begin(), e.end(), comp);
UF uf(e.size());
int res = 0;
for (int i = 0; i < e.size(); i ++) {
        edge ee = e[i];
        if (!uf.same(ee.a, ee.b)) {
                uf.unite(ee.a, ee.b);
                res += ee.cost;
        }
}
