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
    vl h(n + 1, INF);
    rep(i, n) cin >> h[i];

    ll cnt = 0, ans = 0;
    rep(i, n) {
        if (h[i] >= h[i + 1]) {
            cnt++;
        } else {
            ans = max(ans, cnt);
            cnt = 0;
        }
    }
    cout << ans << "\n";

    return 0;
}
