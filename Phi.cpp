int Phi(int n) {
        if (n == 0) return 0;
        int res = n;
        for (int i = 2; i * i <= n; i ++) {
                if (n % i == 0) {
                        res -= res / i; //res *= (i - 1) / i
                        while (n % i == 0) n /= i;
                }
        }
        if (n > 1) res -= res / n;
        return res;
}
