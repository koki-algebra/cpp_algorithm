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

    ll h, w;
    cin >> h >> w;
    vector<string> grid(h);
    rep(i, h) { cin >> grid[i]; }

    vvl left(h, vl(w, 0)), right(h, vl(w, 0)), up(h, vl(w, 0)), down(h, vl(w, 0));
    for (ll i = 0; i < h; i++) {
        ll cur = 0;
        for (ll j = 0; j < w; j++) {
            if (grid[i][j] == '#') {
                cur = 0;
            } else {
                cur++;
            }
            left[i][j] = cur;
        }
    }
    for (ll i = 0; i < h; i++) {
        ll cur = 0;
        for (ll j = w - 1; j >= 0; j--) {
            if (grid[i][j] == '#') {
                cur = 0;
            } else {
                cur++;
            }
            right[i][j] = cur;
        }
    }
    for (ll j = 0; j < w; j++) {
        ll cur = 0;
        for (ll i = 0; i < h; i++) {
            if (grid[i][j] == '#') {
                cur = 0;
            } else {
                cur++;
            }
            down[i][j] = cur;
        }
    }
    for (ll j = 0; j < w; j++) {
        ll cur = 0;
        for (ll i = h - 1; i >= 0; i--) {
            if (grid[i][j] == '#') {
                cur = 0;
            } else {
                cur++;
            }
            up[i][j] = cur;
        }
    }

    ll ans = 0;
    rep(i, h) rep(j, w) {
        if (grid[i][j] == '#') continue;
        ans = max(ans, left[i][j] + right[i][j] + down[i][j] + up[i][j] - 3);
    }
    cout << ans << "\n";

    return 0;
}
