#include <cstdio>
#include <cassert>
using namespace std;

#define unittest_name_helper(counter) unittest_ ## counter
#define unittest_name(counter) unittest_name_helper(counter)
#define unittest __attribute__((constructor)) void unittest_name(__COUNTER__) ()

const int MOD = 1e9 + 7;

const int N = 5000001;
long long fact[N];
long long invfact[N];
long long inv[N];
void init() {
        fact[0] = fact[1] = 1;
        for (int i = 2; i < N; i ++) fact[i] = fact[i - 1] * i % MOD;
        inv[1] = 1;
        for (int i = 2; i < N; i ++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invfact[0] = invfact[1] = 1;
        for (int i = 2; i < N; i ++) invfact[i] = invfact[i - 1] * inv[i] % MOD;
}
long long C(long long n, long long r) {
        if (n < 0 || r < 0 || n < r) return 0;
        return fact[n] * invfact[n - r] % MOD * invfact[r] % MOD;
}
unittest {
        init();
        assert(fact[10] == 3628800);
        assert(fact[123456] == 639390503);
        assert(invfact[10] == 283194722);
        assert(invfact[10000] == 556156297);
        assert(C(10, 3) == 120);
        assert(C(432944, 9324) == 411155797);
}

//long long Inv(long long a) {
//        long long res = 1;
//        long long n = MOD - 2;
//        while (n > 0) {
//                if (n & 1) res = res * a % MOD;
//                a = a * a % MOD;
//                n >>= 1;
//        }
//        return res;
//}
/*
unittest {
        assert(Inv(1) == 1);
        assert(Inv(2) == 500000004);
        assert(Inv(55) == 763636369);
        assert(Inv(123456789) == 18633540);
}
*/

//O(r log r)
//long long C(long long n, long long r) {
//        if (n < r) return 0;
//        if (n - r < r) r = n - r;
//        long long ret = 1;
//        for (int i = 0; i < r; i ++) {
//                ret = ret * (n % MOD) % MOD;
//                n --;
//                ret = ret * Inv(i + 1) % MOD;
//        }
//        return ret;
//}
/*
unittest {
        assert(C(10, 3) == 120);
        assert(C(432944, 9324) == 411155797);
}
*/

//modとらないC
//const int N = 61;
//long long com[N][N];
//void init() {
//        for (int i = 0; i <= N - 1; i ++) {
//                for (int j = 0; j <= i; j ++) {
//                        if (j == 0 || j == i) com[i][j] = 1LL;
//                        else com[i][j] = com[i - 1][j - 1] + com[i - 1][j];
//                } 
//        }
//}
//long long C(int n, int r) { return com[n][r]; }
/*
unittest {
        init();
        assert(C(10, 3) == 120);
        assert(C(45, 33) == 28760021745);
        assert(C(60, 29) == 114449595062769120);
}
*/

int main() {
        return 0;
}
