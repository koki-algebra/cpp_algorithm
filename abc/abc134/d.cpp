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
    vl a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    vl x(n + 1, 0);
    for (ll i = n; i >= 1; i--) {
        ll sum = 0;
        for (ll j = 2 * i; j <= n; j += i) sum ^= x[j];
        x[i] = a[i] ^ sum;
    }

    vl b;
    for (ll i = 1; i <= n; i++) {
        if (x[i] == 1) b.push_back(i);
    }
    cout << b.size() << "\n";
    for (auto v : b) cout << v << " ";
    cout << "\n";

    return 0;
}
