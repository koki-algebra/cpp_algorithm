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
    vector<pll> a(n);
    rep(i, n) {
        ll v;
        cin >> v;
        a[i] = {i, v};
    }
    stable_sort(all(a), [](const pll& a, const pll& b) { return a.second > b.second; });

    rep(i, n) {
        for (auto p : a) {
            if (p.first != i) {
                cout << p.second << "\n";
                break;
            };
        }
    }

    return 0;
}
