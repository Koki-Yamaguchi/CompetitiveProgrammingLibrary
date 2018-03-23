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

//0-origin
template <typename T>
struct FenwickTree {
	vector<T> data;
	FenwickTree(int n) : data(n, 0) {}
        //v[i] += x
	void add(int i, T x) { for (int p = i; p < (int)data.size(); p |= p + 1) data[p] += x; }
        //[0, i)
	T sum(int i) {
		T s = 0;
                for (int p = i - 1; p >= 0; p = (p & (p + 1)) - 1) s += data[p];
		return s;
	}
        //[l, r)
	T sum(int l, int r) { return sum(r) - sum(l); }
};
