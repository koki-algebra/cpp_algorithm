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

// N <= 30 のとき: 半分全列挙 (meet in the middle)
ll solveByMeetInMiddle(ll n, ll w, const vl& values, const vl& weights) {
    ll half = n / 2;

    auto enumerate = [&](ll lo, ll hi) {
        ll m = hi - lo;
        vector<pll> res;  // (weight, value)
        rep(bit, 1LL << m) {
            ll wt = 0, val = 0;
            rep(j, m) {
                if (bit & (1LL << j)) {
                    wt += weights[lo + j];
                    val += values[lo + j];
                }
            }
            if (wt <= w) res.push_back({wt, val});
        }
        sort(all(res));
        // weight昇順に見て、valueが更新されない(支配される)要素を除いた階段を作る
        vector<pll> staircase;
        ll maxVal = -1;
        for (auto& [wt, val] : res) {
            if (val > maxVal) {
                maxVal = val;
                staircase.push_back({wt, maxVal});
            }
        }
        return staircase;
    };

    vector<pll> listA = enumerate(0, half);
    vector<pll> listB = enumerate(half, n);

    ll ans = 0;
    for (auto& [wt, val] : listB) {
        ll rem = w - wt;
        ll idx = upper_bound(all(listA), pll{rem, INF}) - listA.begin() - 1;
        ans = max(ans, val + listA[idx].second);
    }
    return ans;
}

// 全てのw_i <= 1000 のとき: 重量DP (重量の総和は高々 N*1000)
ll solveByWeightDp(ll n, ll w, const vl& values, const vl& weights) {
    ll cap = min(w, 200000LL);
    vl dp(cap + 1, 0);
    rep(i, n) {
        ll wt = weights[i], val = values[i];
        for (ll j = cap; j >= wt; j--) { dp[j] = max(dp[j], dp[j - wt] + val); }
    }
    return dp[cap];
}

// 全てのv_i <= 1000 のとき: 価値DP (dp[価値] = その価値を得る最小重量)
ll solveByValueDp(ll n, ll w, const vl& values, const vl& weights) {
    ll maxVal = 0;
    rep(i, n) maxVal += values[i];
    vl dp(maxVal + 1, INF);
    dp[0] = 0;
    rep(i, n) {
        ll wt = weights[i], val = values[i];
        for (ll j = maxVal; j >= val; j--) { dp[j] = min(dp[j], dp[j - val] + wt); }
    }
    ll ans = 0;
    rep2(v, 0, maxVal + 1) {
        if (dp[v] <= w) ans = v;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, w;
    cin >> n >> w;
    vl values(n), weights(n);
    rep(i, n) cin >> values[i] >> weights[i];

    ll ans;
    if (n <= 30) {
        ans = solveByMeetInMiddle(n, w, values, weights);
    } else if (*max_element(all(weights)) <= 1000) {
        ans = solveByWeightDp(n, w, values, weights);
    } else {
        ans = solveByValueDp(n, w, values, weights);
    }

    cout << ans << "\n";

    return 0;
}
