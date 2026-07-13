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
    vl a(n);
    rep(i, n) cin >> a[i];

    vl sums(n + 1, 0);
    rep(i, n) { sums[i + 1] = sums[i] + a[i]; }

    ll ans = 0;
    rep(i, n) {
        ll lo = i;
        ll hi = n;
        while (lo < hi) {
            auto mid = lo + (hi - lo) / 2;
            // 区間 [i, mid] (0-indexed) の合計
            auto sum = sums[mid + 1] - sums[i];
            if (sum < k) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (lo != n) { ans += n - lo; }
    }
    cout << ans << "\n";

    return 0;
}
