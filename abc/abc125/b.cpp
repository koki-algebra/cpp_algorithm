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

    ll n;
    cin >> n;
    vl v(n), c(n);
    rep(i, n) cin >> v[i];
    rep(i, n) cin >> c[i];

    ll ans = -1;
    rep(bit, 1 << n) {
        ll x = 0, y = 0;
        rep(i, n) {
            if (bit & (1 << i)) {
                x += v[i];
                y += c[i];
            }
            ll diff = x - y;
            if (diff > ans) { ans = diff; }
        }
    }
    cout << ans << "\n";

    return 0;
}
