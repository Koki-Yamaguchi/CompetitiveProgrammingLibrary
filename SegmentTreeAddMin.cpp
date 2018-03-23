//verified CSA_045 C
//区間加算、区間最小値
template<typename Type>
struct LazySegmentTree {
        vector<Type> data, lazy;
        int n;
        LazySegmentTree(int x) {
                n = pow(2, ceil(log2(x)));
                data.resize(2 * n - 1, INF);
                lazy.resize(2 * n - 1, 0);
        }
        void init(int k, Type p) {
                k += n - 1;
                data[k] = p;
                while (k > 0) {
                        k = (k - 1) / 2;
                        data[k] = min(data[k * 2 + 1], data[k * 2 + 2]);
                }
        }
        void add(int a, int b, int x) { return add(a, b, x, 0, 0, n); }
        void add(int a, int b, int x, int k, int l, int r) {
                if (r <= a || b <= l) return;
                if (a <= l && r <= b) {
                        lazy[k] += x;
                        return;
                }
                int m = (l + r) / 2;
                add(a, b, x, k * 2 + 1, l, m);
                add(a, b, x, k * 2 + 2, m, r);
                data[k] = min(data[k * 2 + 1] + lazy[k * 2 + 1], data[k * 2 + 2] + lazy[k * 2 + 2]);
        }
        Type getmin(int a, int b) { return getmin(a, b, 0, 0, n); }
        Type getmin(int a, int b, int k, int l, int r) {
                if (r <= a || b <= l) return INF;
                if (a <= l && r <= b) return data[k] + lazy[k];
                int m = (l + r) / 2;
                Type left = getmin(a, b, k * 2 + 1, l, m);
                Type right = getmin(a, b, k * 2 + 2, m, r);
                return min(left, right) + lazy[k];
        }
};
