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
    vl a(n);
    rep(i, n) cin >> a[i];

    ll sum2b1 = 0;
    rep(i, n) {
        if (i % 2 == 0) {
            sum2b1 += a[i];
        } else {
            sum2b1 -= a[i];
        }
    }
    ll b1 = sum2b1 / 2;

    vl b(n);
    b[0] = b1;
    rep2(i, 1, n) b[i] = a[i - 1] - b[i - 1];
    rep(i, n) {
        cout << 2 * b[i];
        if (i == n - 1) {
            cout << "\n";
        } else {
            cout << " ";
        }
    }

    return 0;
}
