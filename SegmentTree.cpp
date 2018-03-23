template<typename Type>
struct SegmentTree {
        vector<Type> data;
        int n;
        SegmentTree(int x) {
                n = pow(2, ceil(log2(x)));
                data.resize(2 * n - 1, INF); //initial value
        }
        Type merge(Type x, Type y) { //merge function
                return min(x, y);
        }
        void update(int k, Type p) { //update k-th value to p
                k += n - 1;
                data[k] = p;
                while (k > 0) {
                        k = (k - 1) / 2;
                        data[k] = merge(data[k * 2 + 1], data[k * 2 + 2]);
                }
        }
        // [l, r)
        Type query(int a, int b) { return query(a, b, 0, 0, n); }
        Type query(int a, int b, int k, int l, int r) {
                if (r <= a || b <= l) return INF; //initial value
                if (a <= l && r <= b) return data[k];
                int m = (l + r) / 2;
                return merge(query(a, b, k * 2 + 1, l, m), query(a, b, k * 2 + 2, m, r));
        }
};
