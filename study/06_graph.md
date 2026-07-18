# 第4章：グラフアルゴリズム

---

## 4-1. グラフの基礎

グラフは「頂点（ノード）」と「辺（エッジ）」からなるデータ構造。

```
頂点: 0, 1, 2, 3, 4
辺: 0-1, 0-2, 1-3, 2-3, 3-4
```

### グラフの種類

- **無向グラフ**：辺に向きがない（両方向に行ける）
- **有向グラフ**：辺に向きがある（一方向のみ）
- **重み付きグラフ**：辺にコスト（距離）がある

### 隣接リストによる実装

競プロでは隣接リストが基本。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; // 頂点数, 辺数
    cin >> n >> m;
    vector<vector<int>> graph(n); // graph[v] = vに隣接する頂点のリスト

    rep(i, m) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 1-indexed → 0-indexed
        graph[u].push_back(v);
        graph[v].push_back(u); // 無向グラフの場合は両方向に追加
    }
}
```

重み付きグラフの場合：

```cpp
vector<vector<pair<int,int>>> graph(n); // graph[v] = {隣接頂点, 辺の重み}
graph[u].push_back({v, w});
graph[v].push_back({u, w});
```

---

## 4-2. BFS（幅優先探索）

### 用途

- 最短経路（辺のコストがすべて等しいとき）
- 到達可能な頂点を探す
- 最短手数を求める

### 仕組み

始点から近い順に頂点を訪問する。queue を使う。

```
始点 0 → 距離1の頂点 → 距離2の頂点 → ...
```

### 実装

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    rep(i, m) {
        int u, v; cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start = 0;
    vector<int> dist(n, -1); // -1 = 未訪問
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int next : graph[v]) {
            if (dist[next] == -1) { // 未訪問なら
                dist[next] = dist[v] + 1;
                q.push(next);
            }
        }
    }

    // dist[v] = 頂点 v への最短距離（到達不能なら -1）
    rep(i, n) cout << dist[i] << " ";
}
```

### 2次元グリッドでの BFS（頻出）

座標 `(r, c)` は

```cpp
int idx = r * W + c;   // 一次元化
int r = idx / W, c = idx % W; // 復元
```

という式で 1 つの `int` に変換できる。`vector<vector<int>>` や `queue<pair<int,int>>` ではなく `vector<int>` / `queue<int>` 一本で持てるためメモリが連続しキャッシュ効率が良く、`pair` の生成・比較コストも消えるので大きいグリッドでは高速化につながる。

```cpp
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

auto encode = [&](int r, int c) { return r * W + c; };

vector<int> dist(H * W, -1);
queue<int> q;
dist[encode(sr, sc)] = 0;
q.push(encode(sr, sc));

while (!q.empty()) {
    int cur = q.front(); q.pop();
    int r = cur / W, c = cur % W;
    rep(d, 4) {
        int nr = r + dx[d], nc = c + dy[d];
        if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue; // 範囲外
        if (grid[nr][nc] == '#') continue;                      // 壁
        int nidx = encode(nr, nc);
        if (dist[nidx] != -1) continue;                         // 訪問済み
        dist[nidx] = dist[cur] + 1;
        q.push(nidx);
    }
}
```

**注意**：`W` の値は探索中に変えないこと。3次元以上のグリッドでも `idx = (r * H2 + c) * H3 + k` のように掛け算をネストさせれば同様に一次元化できる。

---

## 4-3. DFS（深さ優先探索）

### 用途

- 連結成分の数を数える
- 木の探索
- トポロジカルソート
- 到達可能な頂点を列挙

### 仕組み

BFS が「近い順」に広がっていくのに対し、DFS は「1本の道を行き止まりまで進み、行き止まったら1つ前の分岐まで戻ってまた進む」という探索をする。

```
      0
    /   \
   1     2
   |     |
   3-----+

訪問順（0から）: 0 → 1 → 3 → 2 （3から2へは3-2の辺があれば進み、なければ0まで戻ってから2へ）
```

この「戻る」動作は **スタック（LIFO：後入れ先出し）** の性質そのもの。実装方法は2通りあり、どちらも考え方は同じ。

| 実装 | 使うスタック | 特徴 |
| --- | --- | --- |
| 再帰 | 関数呼び出しスタック（暗黙的） | コードが短く読みやすい。N が大きいとスタックオーバーフローの恐れ |
| 非再帰（明示的な stack） | `stack<int>`（自分で管理） | オーバーフローしない。訪問順が再帰版と前後することがある |

### 実装（再帰）

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int v) {
    visited[v] = true;
    for (int next : graph[v]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    visited.assign(n, false);
    rep(i, m) {
        int u, v; cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 連結成分の数を数える
    int components = 0;
    rep(i, n) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    cout << components << endl;
}
```

### 実装（非再帰・stack）

再帰と同じ探索を、明示的な `stack<int>` を使って書き換えたもの。関数呼び出しを使わないためスタックオーバーフローが起きない。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs_iterative(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true; // push する時点でマークする（同じ頂点の二重pushを防ぐ）

    while (!st.empty()) {
        int v = st.top(); st.pop();
        for (int next : graph[v]) {
            if (!visited[next]) {
                visited[next] = true;
                st.push(next);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    visited.assign(n, false);
    rep(i, m) {
        int u, v; cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 連結成分の数を数える
    int components = 0;
    rep(i, n) {
        if (!visited[i]) {
            dfs_iterative(i);
            components++;
        }
    }
    cout << components << endl;
}
```

**注意**：

- `visited` は「pop した時」ではなく「push した時」にマークする。pop 時にマークすると、同じ頂点が処理前にスタックへ複数回積まれてしまい、無駄な処理や意図しない重複カウントにつながる。
- `stack` は LIFO なので、`graph[v]` に積んだ順と実際に訪れる順は逆になる。そのため訪問順そのものが再帰版と一致するとは限らない（連結成分数のように「順序に依存しない結果」を求める分には問題ない）。
- 再帰の深さが数十万を超えるような入力（一直線に伸びたグラフなど）では再帰版がスタックオーバーフローを起こしうる。そのようなケースでは非再帰版を使う。

---

## 4-4. Dijkstra（ダイクストラ法）

### 用途

重み付きグラフでの**単一始点最短路**。  
辺の重みが非負のときのみ使える。

### 仕組み

priority_queue（最小ヒープ）を使い、現在の最短距離が小さい頂点から順に確定していく。

```
{距離, 頂点} の最小ヒープを使う
```

### 実装

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graph(n); // {隣接頂点, 重み}
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // 無向グラフの場合
    }

    int start = 0;
    vector<ll> dist(n, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start}); // {距離, 頂点}

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d > dist[v]) continue; // すでに更新済みならスキップ
        for (auto [next, w] : graph[v]) {
            if (dist[v] + w < dist[next]) {
                dist[next] = dist[v] + w;
                pq.push({dist[next], next});
            }
        }
    }

    // dist[v] = 始点から v への最短距離（到達不能なら INF）
    rep(i, n) {
        if (dist[i] == INF) cout << -1 << "\n";
        else cout << dist[i] << "\n";
    }
}
```

| アルゴリズム | 計算量 | 用途 |
| --- | --- | --- |
| BFS | $O(V + E)$ | 辺の重みが全部同じ |
| Dijkstra | $O((V + E) \log V)$ | 辺の重みが非負 |
| DFS | $O(V + E)$ | 連結成分、木の探索 |

---

## 4-5. Union-Find（素集合データ構造）

### 用途

- 「2つの頂点が同じ連結成分か？」を高速に判定
- グラフに辺を追加しながら連結性を管理

```cpp
struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(all(parent), 0); // parent[i] = i
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 経路圧縮
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

// 使い方
UnionFind uf(n);
uf.unite(0, 1);       // 0 と 1 をつなげる
uf.same(0, 1);        // true
uf.same(0, 2);        // false（まだつながっていない）
```

---

## 練習問題

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC007C - 幅優先探索](https://atcoder.jp/contests/abc007/tasks/abc007_3) | BFS（グリッド・基本） | ★★☆ |
| [ABC088D - Grid](https://atcoder.jp/contests/abc088/tasks/abc088_d) | BFS（グリッド） | ★★☆ |
| [ABC049D - 連結](https://atcoder.jp/contests/abc049/tasks/arc065_b) | Union-Find | ★★★ |
| [ABC191E - Come Back Quickly](https://atcoder.jp/contests/abc191/tasks/abc191_e) | Dijkstra | ★★★ |
| [ABC196D - Hanjo](https://atcoder.jp/contests/abc196/tasks/abc196_d) | DFS / 全探索 | ★★★ |
