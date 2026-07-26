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

    ll l, r;
    cin >> l >> r;
    if (r - l > 3000)
        cout << 0 << "\n";
    else {
        ll ans = 2018;
        for (ll i = l; i < r; i++) {
            for (ll j = l + 1; j <= r; j++) ans = min(ans, (i * j) % 2019);
        }
        cout << ans << "\n";
    }

    return 0;
}
