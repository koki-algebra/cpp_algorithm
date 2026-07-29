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

    string s;
    cin >> s;
    ll n = s.size();

    vl ans(n, 0);
    vl div = {0};
    for (int i = 0; i < n;) {
        ll j = i;
        while (j < n && s[j] == s[i]) j++;
        div.push_back(j);

        if (s[i] == 'L') {
            ll m = div.size();
            ll a = div[m - 2] - div[m - 3];
            ll b = div[m - 1] - div[m - 2];
            ans[i - 1] = (a + 1) / 2 + b / 2;
            ans[i] = a / 2 + (b + 1) / 2;
        }
        i = j;
    }
    rep(i, n) { cout << ans[i] << " "; }
    cout << "\n";

    return 0;
}
