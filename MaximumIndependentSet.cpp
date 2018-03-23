#include <cstdio>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;
#define unittest_name_helper(counter) unittest_ ## counter
#define unittest_name(counter) unittest_name_helper(counter)
#define unittest __attribute__((constructor)) void unittest_name(__COUNTER__) ()

int MaximumIndependentSet(const int n, const vector<long long> &g) {
        int res = 0;
        function<void (long long, int)> dfs = [&](long long remain, int cnt) {
                for (bool update = true; update; ) {
                        update = false;
                        for (int i = 0; i < n; i ++) if (remain & (1LL << i)) {
                                int deg = __builtin_popcountll(remain & g[i]);
                                if (deg <= 1) {
                                        cnt ++;
                                        remain &= ~((1LL << i) | g[i]);
                                        update = true;
                                }
                        }
                }
                res = max(res, cnt);
                if (remain) {
                        int k = __builtin_ctzll(remain);
                        dfs(remain & ~(1LL << k), cnt);
                        dfs(remain & ~(g[k] | (1LL << k)), cnt + 1);
                }
        };
        dfs((1LL << n) - 1, 0);
        return res;
}

unittest {
        vector<long long> g(40);
        g[0]  = 0b0000000101000000000100000100110000100010;
        g[1]  = 0b0000000000000001000010010100110000000001;
        g[2]  = 0b1000110011000000000010000011000001010000;
        g[3]  = 0b0000101000000000000000000000000000000000;
        g[4]  = 0b1000100000100001010000100000001001000100;
        g[5]  = 0b0000000100000000000000000001010001000001;
        g[6]  = 0b0000100000000000000101000000000100110100;
        g[7]  = 0b0110000000000000000100001100000000000000;
        g[8]  = 0b0010100000100000100000010000000001000000;
        g[9]  = 0b0000110100100000000101101000100000010000;
        g[10] = 0b0011010101000011000000000001000000100011;
        g[11] = 0b0100000001001001001001010000001000000011;
        g[12] = 0b0000000001010001000110000000010000100100;
        g[13] = 0b0010000010000001000000000000000000000100;
        g[14] = 0b0101000101010000001001000000000010000011;
        g[15] = 0b0000100000100000000111100000001010000000;
        g[16] = 0b0000010101000000100000000000100100000010;
        g[17] = 0b0011000010010010001000001000001000010000;
        g[18] = 0b0001110000011000001000001100101001000000;
        g[19] = 0b1000001000000001000000001001000000000110;
        g[20] = 0b1001000000010000100000001001001011000001;
        g[21] = 0b1000001001000010000001100100100000000000;
        g[22] = 0b0100100100000001000000000000000000010000;
        g[23] = 0b0100010000000001000100010000000100000000;
        g[24] = 0b0011011000000100110010000011110000010010;
        g[25] = 0b0010000101000000001000100000010000000000;
        g[26] = 0b0000000110000001000000000000000000000000;
        g[27] = 0b0000000000100000000001000000100000000000;
        g[28] = 0b0000000101000000000101100101000000000000;
        g[29] = 0b0010101001001000000000001000001100010000;
        g[30] = 0b0000001000110010001000010101110000000101;
        g[31] = 0b0011001000000100000000100010000000000100;
        g[32] = 0b0010100000010110010000010100011000100001;
        g[33] = 0b0000000011100001001010000000000000001000;
        g[34] = 0b0000100000000001100001010000011000000100;
        g[35] = 0b0000010100100000010001001000001101011100;
        g[36] = 0b1000000010000001000101100100010000000000;
        g[37] = 0b0000000110100011000000100010010110000000;
        g[38] = 0b0000000000000000110000000100100010000000;
        g[39] = 0b0001000000000000001110000000000000010100;
        assert(MaximumIndependentSet(40, g) == 14);
}

int main() {
        return 0;
}