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

    vl denominations = {1, 6, 36, 216, 1296, 7776, 46656, 9, 81, 729, 6561, 59049};

    vl dp(n + 1, INF);
    dp[0] = 0;
    rep2(x, 1, n + 1) {
        for (auto v : denominations) {
            if (x >= v && dp[x - v] != INF) { dp[x] = min(dp[x], dp[x - v] + 1); }
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
