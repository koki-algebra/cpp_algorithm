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
    rep(i, h) cin >> grid[i];

    ll white_cnt = 0;
    rep(i, h) rep(j, w) {
        if (grid[i][j] == '.') white_cnt++;
    }

    vl dist(h * w, -1);
    auto encode = [&](ll i, ll j) { return i * w + j; };
    queue<ll> q;
    q.push(0);
    dist[0] = 0;

    ll dr[] = {1, -1, 0, 0};
    ll dc[] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        auto r = cur / w;
        auto c = cur % w;

        rep(d, 4) {
            auto nr = r + dr[d];
            auto nc = c + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w || grid[nr][nc] == '#') continue;
            auto nidx = encode(nr, nc);
            if (dist[nidx] != -1) continue;
            dist[nidx] = dist[cur] + 1;
            q.push(nidx);
        }
    }

    auto gidx = encode(h - 1, w - 1);
    if (dist[gidx] == -1) {
        cout << -1 << "\n";
    } else {
        cout << white_cnt - dist[gidx] - 1 << "\n";
    }

    return 0;
}
