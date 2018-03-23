//1-origin
template <typename T>
struct FenwickTree {
        vector<T> data;
        FenwickTree(int n) : data(n + 1, 0) {}
        //data[i] += x
        void add(int i, T x){
                while (i <= (int)data.size()) {
                        data[i] += x;
                        i += i & -i;
                }
        }
        //[1, i)
        T sum(int i){
                T res = 0;
                while (i > 0) {
                        res += data[i];
                        i -= i & -i;
                }
                return res;
        }
        //[l, r)
        T sum(int l, int r) { return sum(r) - sum(l); }
};
long long InversionNumber(const vector<int> &a) {
        FenwickTree<long long> ft(300030);
        long long res = 0;
        for (int i = 0; i < a.size(); i ++) {
                res += i - ft.sum(a[i]);
                ft.add(a[i], 1);
        }
        return res;
}
