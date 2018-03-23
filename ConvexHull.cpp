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
