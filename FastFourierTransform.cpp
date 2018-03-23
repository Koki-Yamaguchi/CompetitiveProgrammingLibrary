typedef complex<double> P;
const int N = 1 << 19;
P x[N], y[N];
const double PI = acos(-1);
const P I (0, 1);
void FFT(P a[], bool inv = false) {
        int n = N;
        double theta = (inv ? -2 : 2) * PI / n;
        for (int m = n; m >= 2; m >>= 1) {
                int mh = m >> 1;
                for (int i = 0; i < mh; i ++) {
                        P w = exp(i * theta * I);
                        for (int j = i; j < n; j += m) {
                                int k = j + mh;
                                P x = a[j] - a[k];
                                a[j] += a[k];
                                a[k] = w * x;
                        }
                }
                theta *= 2;
        }
        int i = 0;
        for (int j = 1; j < n - 1; j ++) {
                for (int k = n >> 1; k > (i ^= k); k >>= 1);
                if (j < i) swap(a[i], a[j]);
        }
}
