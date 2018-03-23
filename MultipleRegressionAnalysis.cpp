#include "bits/stdc++.h"
using namespace std;

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

double Sxy(const vector<double> &x, const vector<double> &y) {
        assert(x.size() == y.size());
        double res = 0;
        double sum = 0;
        int n = x.size();
        for (int i = 0; i < n; i ++) sum += x[i];
        double x_ave = sum / n;
        sum = 0;
        for (int i = 0; i < n; i ++) sum += y[i];
        double y_ave = sum / n;
        for (int i = 0; i < n; i ++) res += (x[i] - x_ave) * (y[i] - y_ave);
        return res;
}

void MultipleRegressionAnalysis(const vector<double> &Object, const Matrix &Explanation) {
        int p = Explanation[0].size();
        int n = Explanation.size();
        Matrix Explanation_Ave_Reduced(n, vector<double> (p));
        vector<double> Exp_ave(p);
        for (int i = 0; i < p; i ++) {
                double sum = 0;
                for (int j = 0; j < n; j ++) {
                        sum += Explanation[j][i];
                }
                Exp_ave[i] = sum / n;
                for (int j = 0; j < n; j ++) {
                        Explanation_Ave_Reduced[j][i] = Explanation[j][i] - Exp_ave[i];
                }
        }
        auto S_a = Mul(Transpose(Explanation_Ave_Reduced), Explanation_Ave_Reduced);
        Matrix Object_Ave_Reduced(n, vector<double> (1));
        double sum = 0;
        for (int i = 0; i < n; i ++) {
                sum += Object[i];
        }
        double Obj_ave = sum / n;
        for (int i = 0; i < n; i ++) {
                Object_Ave_Reduced[i][0] = Object[i] - Obj_ave;
        }
        auto S_b = Mul(Transpose(Explanation_Ave_Reduced), Object_Ave_Reduced);
        Matrix S_a_inv(p, vector<double> (p));
        Inv(S_a, S_a_inv);
        auto Beta = Mul(S_a_inv, S_b);
        cout << "Beta" << endl;
        for (int i = 0; i < p; i ++) cout << Beta[i][0] << endl;
        double Beta_zero = Obj_ave;
        for (int i = 0; i < p; i ++) {
                Beta_zero -= (Beta[i][0] * Exp_ave[i]);
        }
        cout << "Beta_zero = " << Beta_zero << endl;
        vector<double> y_predicted(n);
        for (int i = 0; i < n; i ++) {
                y_predicted[i] = Beta_zero;
                for (int j = 0; j < p; j ++) {
                        y_predicted[i] += Beta[j][0] * Explanation[i][j];
                }
        }
        double R = Sxy(Object, y_predicted) / sqrt(Sxy(Object, Object) * Sxy(y_predicted, y_predicted));;
        cout << "R = " << R << endl;
        vector<double> Eps(n);
        for (int i = 0; i < n; i ++) Eps[i] = Object[i] - y_predicted[i];
        double R2 = Sxy(y_predicted, y_predicted) / Sxy(Object, Object);
        cout << "R2 = " << R2 << endl;
        double RR2 = 1.0 - Sxy(Eps, Eps) / Sxy(Object, Object) * (double) (n - 1) / (double) (n - p - 1);
        cout << "RR2 = " << RR2 << endl;
        double F_zero = Sxy(y_predicted, y_predicted) / Sxy(Eps, Eps) * (double) (n - p - 1) / (double) p;
        cout << "F_zero = " << F_zero << endl;
}

const int data_n = 73;
const int var_n = 7;

vector<vector<double>> parse() {
        string s;
        getline(cin, s);
        vector<vector<double>> data(var_n, vector<double> ());
        while (getline(cin, s)) {
                int sp = 0;
                while (s[sp] != ',') sp ++;
                sp ++;
                int prev = sp;
                int i = 0;
                while (sp < s.size()) {
                        if (s[sp] == ',' && s[sp + 1] == ',') break;
                        while (s[sp] != ',') {
                                sp ++;
                        }
                        double d = stoi(s.substr(prev, sp - prev)); 
                        data[i ++].push_back(d);
                        prev = sp + 1;
                        sp ++;
                }
        }
        return data;
}

void test1(vector<vector<double>> &data) {
        Matrix Explanation(data_n, vector<double> (var_n - 1));
        for (int i = 0; i < data_n; i ++) {
                for (int j = 0; j < var_n - 1; j ++) {
                        Explanation[i][j] = data[j + 1][i];
                }
        }
        MultipleRegressionAnalysis(data[0], Explanation);
}

void test2(vector<vector<double>> &data) {
        Matrix Explanation(data_n, vector<double> (2));
        for (int i = 0; i < data_n; i ++) {
                for (int j = 0; j < 2; j ++) {
                        Explanation[i][j] = data[j + 1][i];
                }
        }
        MultipleRegressionAnalysis(data[0], Explanation);
}

void test3(vector<vector<double>> &data) {
        Matrix Explanation(data_n, vector<double> (2));
        for (int i = 0; i < data_n; i ++) {
                for (int j = 0; j < 2; j ++) {
                        Explanation[i][j] = data[var_n - 1 - j][i];
                }
        }
        MultipleRegressionAnalysis(data[0], Explanation);
}

int main() {
        auto data = parse();
        test1(data);
        test2(data);
        test3(data);
        return 0;
}
