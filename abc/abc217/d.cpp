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

    ll l, q;
    cin >> l >> q;
    set<ll> s; // 切れ目の集合
    rep(i, q) {
        int c;
        ll x;
        cin >> c >> x;
        if (c == 1) {
            s.insert(x);
        } else {
            ll a = 0;
            ll b = l;
            auto ub = s.upper_bound(x);
            if (ub != s.end()) {
                b = *ub; // x より大きな最小の切れ目
            }
            auto lb = s.lower_bound(x);
            if (lb != s.begin()) {
                a = *prev(lb); // x より小さな最大の切れ目
            }
            cout << b - a << "\n";
        }
    }

    return 0;
}
