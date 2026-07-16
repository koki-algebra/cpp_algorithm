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

    ll r, c;
    cin >> r >> c;
    ll sy, sx, gy, gx;
    cin >> sy >> sx >> gy >> gx;
    sy--;
    sx--;
    gy--;
    gx--;
    vector<string> grid(r);
    rep(i, r) cin >> grid[i];

    auto encode = [&](ll i, ll j) { return i * c + j; };

    queue<ll> q;
    vl dist(r * c, -1);
    dist[encode(sy, sx)] = 0;
    q.push(encode(sy, sx));

    const vl di = {-1, 1, 0, 0};
    const vl dj = {0, 0, -1, 1};

    while (!q.empty()) {
        ll cur = q.front();
        q.pop();
        ll ci = cur / c;
        ll cj = cur % c;
        rep(d, 4) {
            ll ni = ci + di[d];
            ll nj = cj + dj[d];
            if (ni < 0 || ni >= r || nj < 0 || nj >= c) continue;
            if (grid[ni][nj] == '#') continue;
            ll nidx = encode(ni, nj);
            if (dist[nidx] != -1) continue;
            dist[nidx] = dist[cur] + 1;
            q.push(nidx);
        }
    }

    cout << dist[encode(gy, gx)] << "\n";

    return 0;
}
