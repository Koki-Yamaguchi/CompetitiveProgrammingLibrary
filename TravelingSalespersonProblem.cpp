//verified by "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A"

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <cassert>

using namespace std;

#define unittest_name_helper(counter) unittest_ ## counter
#define unittest_name(counter) unittest_name_helper(counter)
#define unittest __attribute__((constructor)) void unittest_name(__COUNTER__) ()

static const long long INFL = 0x3f3f3f3f;

//O(2^n n^2), n <= 16
long long TSP(int n, const vector<vector<long long>> &d) {
        vector<vector<long long>> dp(n, vector<long long> (1 << n, -1));
        function<long long (int, int)> dfs = [&](int u, int remain) {
                if (dp[u][remain] != -1) return dp[u][remain];
                if (!remain && u == 0) return dp[u][remain] = 0;
                long long &ret = dp[u][remain];
                ret = INFL;
                for (int v = 0; v < n; v ++) {
                        if (remain & (1 << v)) {
                                ret = min(ret, dfs(v, remain & ~(1 << v)) + d[u][v]);
                        }
                }
                return ret;
        };
        dfs(0, (1 << n) - 1);
        return dp[0][(1 << n) - 1] == INFL ? -1 : dp[0][(1 << n) - 1];
}

unittest {
        //test1
        int n = 4;
        vector<vector<long long>> d(n, vector<long long> (n, INFL));
        d[0][1] = 2;
        d[1][2] = 3;
        d[1][3] = 9;
        d[2][0] = 1;
        d[2][3] = 6;
        d[3][2] = 4;
        assert(TSP(n, d) == 16);

        //test2
        d.clear();
        n = 15;
        d.resize(n);
        for (int i = 0; i < n; i ++) d[i].resize(n);
        for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) d[i][j] = INFL;
        d[0][3] = 189;
        d[0][5] = 345;
        d[0][6] = 638;
        d[0][9] = 44;
        d[0][10] = 644;
        d[0][13] = 993;
        d[1][0] = 41;
        d[1][2] = 769;
        d[1][4] = 916;
        d[1][5] = 739;
        d[1][8] = 373;
        d[1][9] = 717;
        d[1][10] = 728;
        d[1][11] = 533;
        d[1][12] = 466;
        d[2][0] = 850;
        d[2][1] = 785;
        d[2][3] = 230;
        d[2][4] = 628;
        d[2][6] = 203;
        d[2][7] = 61;
        d[2][10] = 946;
        d[3][0] = 666;
        d[3][1] = 745;
        d[3][2] = 421;
        d[3][4] = 500;
        d[3][5] = 251;
        d[3][8] = 714;
        d[3][10] = 697;
        d[3][11] = 669;
        d[3][12] = 88;
        d[3][14] = 690;
        d[4][6] = 167;
        d[4][7] = 525;
        d[4][9] = 646;
        d[4][11] = 855;
        d[5][6] = 938;
        d[5][7] = 244;
        d[5][12] = 279;
        d[6][1] = 22;
        d[6][7] = 980;
        d[6][8] = 751;
        d[6][11] = 18;
        d[6][14] = 545;
        d[7][0] = 51;
        d[7][3] = 7;
        d[7][5] = 348;
        d[7][6] = 593;
        d[7][8] = 232;
        d[7][13] = 300;
        d[8][0] = 803;
        d[8][3] = 786;
        d[8][4] = 926;
        d[8][5] = 682;
        d[8][6] = 18;
        d[8][7] = 723;
        d[8][9] = 806;
        d[8][12] = 541;
        d[8][13] = 266;
        d[8][14] = 38;
        d[9][0] = 84;
        d[9][1] = 419;
        d[9][3] = 174;
        d[9][4] = 7;
        d[9][7] = 375;
        d[9][8] = 281;
        d[9][10] = 178;
        d[9][13] = 912;
        d[9][14] = 990;
        d[10][0] = 575;
        d[10][3] = 105;
        d[10][4] = 61;
        d[10][6] = 958;
        d[10][11] = 648;
        d[10][13] = 793;
        d[11][0] = 262;
        d[11][2] = 485;
        d[11][4] = 950;
        d[11][5] = 786;
        d[11][8] = 634;
        d[11][10] = 399;
        d[11][12] = 805;
        d[11][13] = 194;
        d[11][14] = 787;
        d[12][2] = 858;
        d[12][3] = 399;
        d[12][5] = 512;
        d[12][6] = 2;
        d[12][9] = 334;
        d[12][10] = 97;
        d[12][11] = 700;
        d[12][13] = 283;
        d[12][14] = 798;
        d[13][1] = 387;
        d[13][3] = 263;
        d[13][5] = 599;
        d[13][6] = 116;
        d[13][9] = 600;
        d[13][11] = 131;
        d[13][14] = 852;
        d[14][1] = 990;
        d[14][2] = 430;
        d[14][4] = 96;
        d[14][6] = 932;
        d[14][8] = 616;
        d[14][9] = 955;
        d[14][12] = 716;
        assert(TSP(n, d) == 2356);
}

int main() {
        return 0;
}
