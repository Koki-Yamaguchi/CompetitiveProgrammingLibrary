vector<int> BitsetGcd(vector<int> s, vector<int> t) {
        int n = s.size(), m = t.size();
        if (n < m) return BitsetGcd(t, s);
        if (!m) return s;
        for (int i = 0; i < m; i ++) s[i] ^= t[i];
        int l = n;
        for (int i = 0; i < n; i ++) {
                if (s[i]) {
                        l = min(l, i);
                        break;
                }
        }
        vector<int> a(n - l);
        for (int i = 0; i < n - l; i ++) a[i] = s[l + i];
        return BitsetGcd(t, a);
}
bitset<N> BitsetGcd(bitset<N> s, bitset<N> t) {
        int n = Len(s), m = Len(t);
        if (n < m) return gcd(t, s);
        if (t.none()) return s;
        int d = n - m;
        bitset<N> u = t;
        u <<= d;
        s ^= u;
        return gcd(t, s);
}
