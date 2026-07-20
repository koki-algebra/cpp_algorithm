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
    ll v1 = 1, v2 = 1;
    rep(i, n) {
        ll t, a;
        cin >> t >> a;
        ll x = (v1 + t - 1) / t;
        ll y = (v2 + a - 1) / a;
        v1 = t * max(x, y);
        v2 = a * max(x, y);
    }
    cout << v1 + v2 << "\n";

    return 0;
}
