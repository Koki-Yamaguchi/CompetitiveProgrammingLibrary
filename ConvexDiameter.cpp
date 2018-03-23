#include "bits/stdc++.h"
using namespace std;

//幾何ライブラリ
const double EPS = 1e-8;
const double INFD = 1e12;
typedef complex<double> point;
namespace std {
        bool operator<(const point &a, const point &b) {
                return abs(real(a) - real(b)) > EPS ? real(a) < real(b) : imag(a) < imag(b);
        }
}
//形状
struct circle { point p; double r; };
struct line { point s,  t; };
struct segment { point s, t; };
//関数
double dist(point &a, point &b) { return sqrt(norm(a - b)); }
double dist_sq(point &a, point &b) { return norm(a - b); }
double dot(point &a, point &b) { return real(conj(a) * b); }
double cross(point &a, point &b) { return imag(conj(a) * b); }
//反時計周りに見ること
double ccw(point a, point b, point c) { //参照しないこと
        b -=a, c -= a;
        if (cross(b, c) > 0)   return +1; //反時計回り
        if (cross(b, c) < 0)   return -1; //時計回り
        if (dot(b, c) < 0)     return +2; //直線上で c -> a -> b
        if (norm(b) < norm(c)) return -2; //直線上で a -> b -> c または a == b
                               return  0; //直線上で a -> c -> b または a == b == c または a == c または b == c
}

vector<point> ConvexHull(vector<point> p) {
        int n = p.size(), k = 0;
        sort(p.begin(), p.end());
        vector<point> res(2 * n);
        for (int i = 0; i < n; res[k ++] = p[i ++]) {
                while (k >= 2 && ccw(res[k - 2], res[k - 1], p[i]) <= 0) k --;
                //while (k >= 2 && ccw(res[k - 2], res[k - 1], p[i]) == -1) k --; //同一直線上の点をすべてとる
        }
        for (int i = n - 2, t = k + 1; i >= 0; res[k ++] = p[i --]) { 
                while (k >= t && ccw(res[k - 2], res[k - 1], p[i]) <= 0) k --;
                //while (k >= t && ccw(res[k - 2], res[k - 1], p[i]) == -1) k --;
        }
        res.resize(k - 1);
        return res;
}


double ConvexDiameter(vector<point> p) {
        p = ConvexHull(p);
        int n = p.size();
        if (n == 2) return dist(p[0], p[1]);
        int i = 0, j = 0;
        for (int k = 0; k < n; k ++) {
                if (imag(p[k]) < imag(p[i])) i = k;
                if (imag(p[k]) > imag(p[j])) j = k;
        }
        double res = 0;
        int si = i, sj = j;
        int maxi, maxj;
        while (si != j || sj != i) {
                point pi = p[(i + 1) % n] - p[i];
                point pj = p[(j + 1) % n] - p[j];
                if (cross(pi, pj) >= 0) j = (j + 1) % n;
                else i = (i + 1) % n;
                if (dist(p[i], p[j]) > res) {
                        res = dist(p[i], p[j]);
                        maxi = i, maxj = j;
                }
        }
        return res; //必要ならばmaxiとmaxjを返す
}


int main() {
        int n;
        cin >> n;
        vector<point> ps;
        for (int i = 0; i < n; i ++) {
                double x, y;
                cin >> x >> y;
                point p(x, y);
                ps.push_back(p);
        }
        cout << ConvexDiameter(ps) << endl;
        return 0;
}

