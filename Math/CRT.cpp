#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return g;
}

ll mod_inverse(ll a, ll mod) {
    ll x, y;
    extended_gcd(a, mod, x, y);

    x %= mod;
    if (x < 0) x += mod;

    return x;
}

ll CRT(vector<ll>& a, vector<ll>& m) {
    int n = a.size();

    ll M = 1;
    for (auto x : m)
        M *= x;

    ll ans = 0;

    for (int i = 0; i < n; i++) {
        ll Mi = M / m[i];

        ll inv = mod_inverse(Mi, m[i]);

        ans = (ans + a[i] * Mi % M * inv % M) % M;
    }

    ans %= M;
    if (ans < 0) ans += M;

    return ans;
}

int main() {
    vector<ll> a = {2, 3, 2};
    vector<ll> m = {3, 5, 7};
    ///  CRT(a, m) = a[i] % m[i] 

    cout << CRT(a, m) << '\n'; // 23
}
