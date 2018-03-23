typedef double Type;
typedef vector<vector<Type>> Matrix;
int GetRank(Matrix a) {
        int h = a.size(), w = a[0].size();
        int res = 0, now = 0;
        for (int i = 0; i < h; i ++) {
                Type ma = 0.0;
                int pivot;
                for (int j = i; j < h; j ++) {
                        if (a[j][now] > ma) {
                                ma = a[j][now];
                                pivot = j;
                        }
                }
                if (ma == 0.0) {
                        now ++;
                        if (now == w) break;
                        i --;
                        continue;
                }
                if (pivot != i) {
                        for (int j = 0; j < w; j ++) { 
                                swap(a[i][j], a[pivot][j]);
                        }

                }
                Type tmp = 1.0 / a[i][now];
                for (int j = 0; j < w; j ++) a[i][j] *= tmp;
                for (int j = 0; j < h; j ++) {
                        if (i != j) {
                                Type tmp2 = a[j][now];
                                for (int k = 0; k < w; k ++) {
                                        a[j][k] -= a[i][k] * tmp2;
                                }
                        }
                }
                res ++;
        }
        return res;
}
bool Inv(Matrix a, Matrix &inv) {
        assert(a.size() == a[0].size() && inv.size() == inv[0].size());
        int n = a.size();
        for (int i = 0; i < n; i ++) {
                for (int j = 0; j < n; j ++) {
                        inv[i][j] = (i == j ? 1.0 : 0.0);
                }
        }
        for (int i = 0; i < n; i ++) {
                Type ma = 0.0;
                int pivot;
                for (int j = i; j < n; j ++) { 
                        if (a[j][i] > ma) {
                                ma = a[j][i];
                                pivot = j;
                        }
                }
                if (ma == 0.0) return false;
                if (pivot != i) {
                        for (int j = 0; j < n; j ++) { 
                                swap(a[i][j], a[pivot][j]);
                                swap(inv[i][j], inv[pivot][j]);
                        }

                }
                Type tmp = 1.0 / a[i][i];
                for (int j = 0; j < n; j ++) {
                        a[i][j] *= tmp;
                        inv[i][j] *= tmp;
                }
                for (int j = 0; j < n; j ++) {
                        if (i != j) {
                                Type tmp2 = a[j][i];
                                for (int k = 0; k < n; k ++) {
                                        a[j][k] -= a[i][k] * tmp2;
                                        inv[j][k] -= inv[i][k] * tmp2;
                                }
                        }
                }
        }
        return true;
}
Matrix Transpose(const Matrix &a) {
        int h = a.size(), w = a[0].size();
        Matrix b(w, vector<Type> (h));
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        b[j][i] = a[i][j];
                }
        }
        return b;
}
Matrix Add(const Matrix &a, const Matrix &b, bool minus = false) {
        assert(a.size() == b.size() && a[0].size() == b[0].size());
        int h = a.size(), w = a[0].size();
        Matrix c(h, vector<Type> (w));
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        c[i][j] = a[i][j] + (minus ? -1 : 1) * b[i][j];
                }
        }
        return c;
}
Matrix Sub(const Matrix &a, const Matrix &b) {
        return Add(a, b, true);
}
Matrix Mul(const Matrix &a, const Matrix &b) {
        assert(a[0].size() == b.size());
        Matrix c(a.size(), vector<Type> (b[0].size()));
        for (int i = 0; i < a.size(); i ++) {
                for (int k = 0; k < b.size(); k ++) {
                        for (int j = 0; j < b[0].size(); j ++) {
                                c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
                        }
                }
        }
        return c;
}
Matrix MulConst(const Type &a, const Matrix &x) {
        Matrix res(x.size(), vector<Type> (x[0].size()));
        for (int i = 0; i < x.size(); i ++) {
                for (int j = 0; j < x[0].size(); j ++) {
                        res[i][j] = x[i][j] * a;
                }
        }
        return res;
}
Matrix Pow(Matrix a, long long n) {
        assert(a.size() == a[0].size());
        Matrix b(a.size(), vector<Type> (a.size()));
        for (int i = 0; i < a.size(); i ++) {
                b[i][i] = 1;
        }
        while (n > 0) {
                if (n & 1) b = Mul(b, a);
                a = Mul(a, a);
                n >>= 1;
        }
        return b;
}
void PrintMatrix(const Matrix &a) {
        int h = a.size(), w = a[0].size();
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        cout << a[i][j] << (j == w - 1 ? '\n' : ' ');
                }
        }
}
int LinearEquationSolver(Matrix a, Matrix &x, Matrix b) {
        assert(a.size() == a[0].size() && a.size() == x.size() && a.size() == b.size());
        int n = a.size();
        Matrix inv(n, vector<Type> (n));
        if (Inv(a, inv)) {
                x = Mul(inv, b);
                return 1;
        } else {
                Matrix ax(n, vector<Type> (n + 1));
                for (int i = 0; i < n; i ++) {
                        for (int j = 0; j < n; j ++) {
                                ax[i][j] = a[i][j];
                        }
                }
                for (int i = 0; i < n; i ++) ax[i][n] = b[i][0];
                if (GetRank(ax) == GetRank(a)) return 0;
                else return -1;
        }
}
Matrix ToMatrix(const vector<Type> &x) {
        Matrix res(x.size(), vector<Type> (1));
        for (int i = 0; i < x.size(); i ++) res[i][0] = x[i];
        return res;
}
