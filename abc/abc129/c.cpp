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
    set<ll> a;
    rep(i, m) {
        ll v;
        cin >> v;
        a.insert(v);
    }

    vl dp(n + 1);
    dp[0] = 1;
    rep(i, n + 1) {
        if (a.count(i)) continue;
        if (i >= 1 && !a.count(i - 1)) {
            dp[i] += dp[i - 1];
            dp[i] %= MOD;
        }
        if (i >= 2 && !a.count(i - 2)) {
            dp[i] += dp[i - 2];
            dp[i] %= MOD;
        }
    }
    cout << dp[n] << "\n";

    return 0;
}
