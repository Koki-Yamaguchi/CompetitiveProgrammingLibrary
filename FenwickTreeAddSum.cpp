//1-origin FenwickTree
//add(l, r, x, ft1, ft2) := add x to the segment [l, r]
//sum(l, r, ft1, ft2) := return the sum of the segment [l, r]
template <typename T>
struct FenwickTree {
        vector<T> data;
        FenwickTree(int n) : data(n + 1, 0) {}
        void add(int i, T x){
                while (i <= (int)data.size()) {
                        data[i] += x;
                        i += i & -i;
                }
        }
        T sum(int i){
                T res = 0;
                while (i > 0) {
                        res += data[i];
                        i -= i & -i;
                }
                return res;
        }
        T sum(int l, int r) { return sum(r) - sum(l); }
};
void add(int l, int r, int x, FenwickTree<int> &ft1, FenwickTree<int> &ft2) {
        ft2.add(l, -x * (l - 1));
        ft1.add(l, x);
        ft2.add(r + 1, x * r);
        ft1.add(r + 1, -x);
}
long long sum(int l, int r, FenwickTree<int> &ft1, FenwickTree<int> &ft2) {
        long long res = 0;
        res += ft2.sum(r) + ft1.sum(r) * r;
        res -= ft2.sum(l - 1) + ft1.sum(l - 1) * (l - 1);
        return res;
}
