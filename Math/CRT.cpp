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

// returns {x, lcm(m1,m2)}, or {-1,-1} if impossible
pair<ll, ll> merge_crt(ll a1, ll m1, ll a2, ll m2) {
    ll x, y;
    ll g = ext_gcd(m1, m2, x, y);
 
    if ((a2 - a1) % g != 0) return {-1, -1};
 
    ll lcm = m1 / g * m2;
 
    ll k = (a2 - a1) / g;
 
    x = (x % (m2 / g) + (m2 / g)) % (m2 / g);
 
    ll add = (k % (m2 / g) + (m2 / g)) % (m2 / g);
    x = (x * add) % (m2 / g);
 
    ll res = (a1 + m1 * x) % lcm;
    if (res < 0) res += lcm;
 
    return {res, lcm};
}

int main() {
    vector<ll> a = {2, 3, 2};
    vector<ll> m = {3, 5, 7};
    ///  CRT(a, m) = a[i] % m[i] 


             ll a = 0, m = 1;
            bool ok = true;
 
            for (int i = L; i <= R; i++) {
                auto res = merge_crt(a, m, A[i], M[i]);
                if (res.first == -1) {
                    ok = false;
                    break;
                }
                a = res.first;
                m = res.second;
            }
 
            if (!ok) cout << -1 << "\n";
            else cout << a << "\n";
    
    cout << CRT(a, m) << '\n'; // 23
}
