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
    priority_queue<ll, vl, greater<ll>> pq;
    rep(i, n) {
        ll a;
        cin >> a;
        pq.push(a);
    }

    vector<pll> ops(m);
    rep(i, m) {
        ll b, c;
        cin >> b >> c;
        ops[i] = make_pair(c, b);
    }
    sort(rall(ops));

    for (auto [c, b] : ops) {
        rep(j, b) {
            if (pq.empty() || pq.top() >= c) break;
            pq.pop();
            pq.push(c);
        }
    }

    vl vals;
    while (!pq.empty()) {
        vals.push_back(pq.top());
        pq.pop();
    }
    sort(rall(vals));

    ll ans = 0;
    rep(i, n) ans += vals[i];
    cout << ans << "\n";

    return 0;
}
