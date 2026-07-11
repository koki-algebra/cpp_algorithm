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
    vvl s(m);
    rep(i, m) {
        ll k;
        cin >> k;
        rep(j, k) {
            ll a;
            cin >> a;
            a--;
            s[i].push_back(a);
        }
    }
    vl p(m);
    rep(i, m) { cin >> p[i]; }

    ll ans = 0;
    rep(bit, (1 << n)) {
        bool ok = true;
        rep(i, m) {
            ll cnt = 0;
            for (auto v : s[i]) {
                if (bit & (1 << v)) { cnt++; }
            }
            if (cnt % 2 != p[i]) { ok = false; }
        }
        if (ok) { ans++; }
    }

    cout << ans << "\n";

    return 0;
}
