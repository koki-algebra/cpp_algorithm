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
    vector<pll> tasks(n);
    rep(i, n) { cin >> tasks[i].first >> tasks[i].second; }
    sort(all(tasks), [](const pll& a, const pll& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    ll sum = 0;
    rep(i, n) {
        sum += tasks[i].first;
        if (sum > tasks[i].second) {
            cout << "No" << "\n";
            return 0;
        }
    }
    cout << "Yes" << "\n";

    return 0;
}
