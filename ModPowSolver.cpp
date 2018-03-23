long long ModPow(long long x, long long n, long long m) {
        long long res = 1;
        while (n > 0) {
                if (n & 1) res = res * x % m;
                x = x * x % m;
                n >>= 1;
        }
        return res;
}
long long Phi(long long n) {
        if (n == 0) return 0;
        long long res = n;
        for (int i = 2; (long long) i * i <= n; i ++) {
                if (n % i == 0) {
                        res -= res / i; //res *= (i - 1) / i
                        while (n % i == 0) n /= i;
                }
        }
        if (n > 1) res -= res / n;
        return res;
}
long long Extgcd(long long a, long long b, long long& x, long long& y) {
        long long d = a;
        if (b != 0) {
                d = Extgcd(b, a % b, y, x);
                y -= (a / b) * x;
        } else {
                x = 1;
                y = 0;
        }
        return d;
}
//return the solution to $\ x^k \equiv b (mod m)\ $
//both gcd(b, m) and gcd(k, phi(m)) should be 1
long long ModPowSolver(long long k, long long b, long long m) {
        long long p = Phi(m);
        assert(__gcd(b, m) == 1);
        assert(__gcd(k, p) == 1);
        long long u, v;
        Extgcd(k, p, u, v);
        if (u < 0) u += p;
        long long res = ModPow(b, u, m);
        return res;
}
