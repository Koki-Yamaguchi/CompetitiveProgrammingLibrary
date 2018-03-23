#include "bits/stdc++.h"
using namespace std;

#define OUT(x)  cerr << #x << " = " << x << endl;
#define all(x)  x.begin(), x.end()
#define mp      make_pair
#define pii     pair<int, int>
#define piii    pair<int, pair<int, int>>

struct Rectangle { 
        int height, pos;
        Rectangle(int h, int p) : height(h), pos(p) {}
};
//1と0のグリッドにおいて1のマスのみを使って作る長方形の中で面積が最大のものの面積を返す
int LargestRectangle(vector<vector<int> > &s, int h, int w) { 
        vector<vector<int> > t(h, vector<int> (w));
        for (int x = 0; x < w; x ++) for (int y = 0; y < h; y ++) {
                if (s[y][x] == 0) t[y][x] = 0;
                else t[y][x] = (y > 0) ? t[y - 1][x] + 1 : 1;
        }
        int res = 0;
        for (int y = 0; y < h; y ++) { 
                stack<Rectangle> st;
                int ma = 0;
                t[y].resize(t.size() + 1);
                t[y][w] = 0;
                for (int x = 0; x <= w; x ++) {
                        Rectangle rect(t[y][x], x);
                        if (st.empty()) {
                                st.push(rect);
                        } else {
                                if (st.top().height < rect.height) {
                                        st.push(rect);
                                } else if (st.top().height > rect.height) {
                                        int target = x;
                                        while (!st.empty() && st.top().height >= rect.height) {
                                                Rectangle prev = st.top(); st.pop();
                                                ma = max(ma, prev.height * (x - prev.pos));
                                                target = prev.pos;
                                        }
                                        rect.pos = target;
                                        st.push(rect);
                                }
                        }
                }
                res = max(res, ma);
        }
        return res;
}

int main() {
        int h, w;
        cin >> h >> w;
        vector<vector<int> > s(h, vector<int> (w));
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        cin >> s[i][j];
                }
        }
        int ans = LargestRectangle(s, h, w);
        cout << ans << endl;
        return 0;
}
