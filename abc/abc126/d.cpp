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
    vector<vector<pll>> graph(n);
    rep(i, n - 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    vl ans(n, 0);
    stack<tuple<ll, ll, ll>> st;
    st.push(make_tuple(0, -1, 1));
    while (!st.empty()) {
        auto [v, p, c] = st.top();
        st.pop();
        ans[v] = c;

        for (auto e : graph[v]) {
            if (e.first == p) continue;
            if (e.second & 1) {
                st.push(make_tuple(e.first, v, 1-c));
            } else {
                st.push(make_tuple(e.first, v, c));
            }
        }
    }

    rep(i, n) cout << ans[i] << "\n";

    return 0;
}
