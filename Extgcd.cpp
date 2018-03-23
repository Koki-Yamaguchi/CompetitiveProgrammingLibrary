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
