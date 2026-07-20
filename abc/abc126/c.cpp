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

    ll n, k;
    cin >> n >> k;

    double ans = 0.0;
    rep2(i, 1, n + 1) {
        ll j = 0;
        ll v = i;
        while (v < k) {
            v *= 2;
            j++;
        }
        ans += 1.0 / double(n) * pow(0.5, j);
    }
    cout << fixed << setprecision(12) << ans << "\n";

    return 0;
}
