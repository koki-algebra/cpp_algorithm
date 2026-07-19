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

struct UnionFind {
    vl parent, rank;

    UnionFind(ll n) : parent(n), rank(n, 0) { iota(all(parent), 0); };

    ll find(ll x) {
        if (parent[x] == x) { return x; }
        return parent[x] = find(parent[x]);
    }

    void unite(ll x, ll y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }

    bool same(ll x, ll y) { return find(x) == find(y); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k, l;
    cin >> n >> k >> l;
    UnionFind road(n), train(n);
    rep(i, k) {
        ll p, q;
        cin >> p >> q;
        p--;
        q--;
        road.unite(p, q);
    }
    rep(i, l) {
        ll r, s;
        cin >> r >> s;
        r--;
        s--;
        train.unite(r, s);
    }

    map<pair<ll, ll>, ll> nums;
    rep(i, n) { nums[make_pair(road.find(i), train.find(i))]++; }

    rep(i, n) { cout << nums[make_pair(road.find(i), train.find(i))] << " "; }
    cout << "\n";

    return 0;
}
