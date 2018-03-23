//N以下の素数列挙。O(N log log N)
int N = 100000;
vector<int> primes;
vector<bool> is_prime(N + 1, true);
void init() {
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= N; i ++) {
                if (is_prime[i]) {
                        primes.push_back(i);
                        for (int j = i + i; j <= N; j += i) is_prime[j] = false;
                }
        }
}
