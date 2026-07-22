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

    ll n, m;
    cin >> n >> m;

    vl diff(n + 1, 0);
    rep(i, m) {
        ll l, r;
        cin >> l >> r;  // 1-indexted closed interval
        diff[l - 1]++;
        diff[r]--;
    }

    vl a(n);
    a[0] = diff[0];
    rep2(i, 1, n) a[i] = a[i - 1] + diff[i];

    ll ans = 0;
    rep(i, n) {
        if (a[i] == m) ans++;
    }
    cout << ans << "\n";

    return 0;
}
