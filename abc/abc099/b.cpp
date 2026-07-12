#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;

#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep2(i, a, b) for (ll i = (ll)(a); i < (ll)(b); i++)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

const ll INF = 1e18;
const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 西: 1 + ... + n とすると
    // 東: 1 + ... + n + (n+1) となる.
    // a = 1 + ... + n - x
    // b = 1 + ... + n + (n+1) - x
    // b - a = n + 1
    // n = b - a - 1
    // x = 1 + ... + n - a = (1 + n) * n / 2 - a

    ll a, b;
    cin >> a >> b;

    ll n = b - a - 1;
    ll ans = (1 + n) * n / 2 - a;
    cout << ans << "\n";

    return 0;
}
