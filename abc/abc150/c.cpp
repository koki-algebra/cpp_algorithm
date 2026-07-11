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
    vl p(n), q(n);
    rep(i, n) cin >> p[i];
    rep(i, n) cin >> q[i];

    auto v = p;
    sort(all(v));

    ll a = 0, b = 0, i = 0;
    do {
        if (v == p) { a = i; }
        if (v == q) { b = i; }
        i++;
    } while (next_permutation(all(v)));

    cout << abs(a - b) << "\n";

    return 0;
}
