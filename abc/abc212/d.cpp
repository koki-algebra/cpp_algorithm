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

    ll q;
    cin >> q;
    priority_queue<ll, vl, greater<ll>> pq;
    ll add = 0;
    rep(i, q) {
        int p;
        cin >> p;
        if (p == 1) {
            ll x;
            cin >> x;
            pq.push(x - add);
        } else if (p == 2) {
            ll x;
            cin >> x;
            add += x;
        } else {
            auto x = pq.top() + add;
            cout << x << "\n";
            pq.pop();
        }
    }

    return 0;
}
