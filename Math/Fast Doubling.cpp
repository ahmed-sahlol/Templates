#include <bits/stdc++.h>

#define int long long

#define el '\n'

using namespace std;


/// f[2k] = f[k](2f[k+1] - f[k])
/// f[2k + 1] = f[k+1] ^ 2 + f[k] ^ 2
/// fib(n) = {F(n), F(n+1)} => LOG(n)
const int MOD = 1e9 + 7;

pair<long long, long long> fib(long long n) {
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n >> 1);
    long long c = a * ((2 * b % MOD - a + MOD) % MOD) % MOD;
    long long d = (a * a % MOD + b * b % MOD) % MOD;
    if (n & 1) return {d, (c + d) % MOD};
    return {c, d};
}

void work() {
    cout << fib(1000000000000000000).second << el;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ": ";
        work();
    }
}
