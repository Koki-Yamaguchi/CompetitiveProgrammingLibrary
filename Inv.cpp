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

long long Inv(long long a) {
        long long x, y;
        Extgcd(a, MOD, x, y);
        return (x % MOD + MOD) % MOD;
}

long long Inv(long long a) {
        long long res = 1;
        long long n = MOD - 2;
        while (n > 0) {
                if (n & 1) res = res * a % MOD;
                a = a * a % MOD;
                n >>= 1;
        }
        return res;
}
