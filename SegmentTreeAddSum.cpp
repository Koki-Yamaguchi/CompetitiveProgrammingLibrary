template<typename Type>
struct LazySegmentTree {
        vector<Type> data, lazy;
        int n;
        LazySegmentTree(int x) {
                n = pow(2, ceil(log2(x)));
                data.resize(2 * n - 1, 0);
                lazy.resize(2 * n - 1, 0);
        }
        void add(int a, int b, int x) { add(a, b, x, 0, 0, n); }
        void add(int a, int b, int x, int k, int l, int r) {
                if (a <= l && r <= b) data[k] += x;
                else if (l < b && a < r) {
                        lazy[k] += (min(b, r) - max(a, l)) * x;
                        add(a, b, x, k * 2 + 1, l, (l + r) / 2);
                        add(a, b, x, k * 2 + 2, (l + r) / 2, r);
                }
        }
        Type sum(int a, int b) { return sum(a, b, 0, 0, n); }
        Type sum(int a, int b, int k, int l, int r) {
                if (b <= l || r <= a) return 0;
                else if (a <= l && r <= b) return data[k] * (r - l) + lazy[k];
                else {
                        Type res = (min(b, r) - max(a, l)) * data[k];
                        res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
                        res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
                        return res;
                }
        }
};
