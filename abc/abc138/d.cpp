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

    ll n, q;
    cin >> n >> q;

    vvl graph(n);
    rep(i, n - 1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vl ans(n);
    rep(i, q) {
        ll p, x;
        cin >> p >> x;
        p--;
        ans[p] += x;
    }

    vector<bool> seen(n, false);
    stack<pll> st;  // {index, parent}
    st.push(make_pair(0, -1));

    while (!st.empty()) {
        auto [v, p] = st.top();
        st.pop();
        seen[v] = true;
        if (p != -1) { ans[v] += ans[p]; }
        for (auto nv : graph[v]) {
            if (seen[nv]) continue;
            st.push(make_pair(nv, v));
        }
    }
    rep(i, n) { cout << ans[i] << " "; }
    cout << "\n";

    return 0;
}
