# 第2章：累積和・二分探索・しゃくとり法

C/D 問題で頻出の「前処理で高速化する」テクニック3本です。

---

## 2-1. 累積和（Prefix Sum）

### 発想

「区間 $[l, r]$ の合計を何度も求めたい」→ 毎回 $O(N)$ で計算すると $O(NQ)$ でTLE。
事前に累積和を計算しておけば、各クエリを $O(1)$ で処理できる。

### 仕組み

```
配列 a:     3  1  4  1  5  9  2  6
累積和 S: 0  3  4  8  9 14 23 25 31
          ↑
          S[0] = 0 にする（番兵）
```

区間 $[l, r]$（0-indexed）の合計 $= S[r+1] - S[l]$

### 実装

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 累積和の構築
    vector<ll> S(n + 1, 0);
    for (int i = 0; i < n; i++) {
        S[i + 1] = S[i] + a[i];
    }

    // 区間 [l, r] の合計（0-indexed, 両端含む）
    auto sum = [&](int l, int r) -> ll {
        return S[r + 1] - S[l];
    };

    // 例：区間 [1, 4] の合計
    cout << sum(1, 4) << endl; // 1+4+1+5 = 11
}
```

### 2次元累積和

```cpp
// H×W のグリッドで矩形領域の合計を O(1) で求める
vector<vector<ll>> S(H + 1, vector<ll>(W + 1, 0));

// 構築
for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
        S[i+1][j+1] = S[i][j+1] + S[i+1][j] - S[i][j] + a[i][j];

// 矩形 (r1,c1)〜(r2,c2) の合計（0-indexed）
ll rect_sum = S[r2+1][c2+1] - S[r1][c2+1] - S[r2+1][c1] + S[r1][c1];
```

---

## 2-2. 二分探索（Binary Search）

### 発想

ソート済み配列の中から目的の値を $O(\log N)$ で探す。
「答えを二分探索する」という使い方も超重要。

### `lower_bound` / `upper_bound`

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 4, 4, 5, 7, 9};
    //               0  1  2  3  4  5  6

    // lower_bound: x 以上の最初の位置
    auto it = lower_bound(a.begin(), a.end(), 4);
    cout << (it - a.begin()) << endl; // 2

    // upper_bound: x より大きい最初の位置
    auto it2 = upper_bound(a.begin(), a.end(), 4);
    cout << (it2 - a.begin()) << endl; // 4

    // x が含まれる個数 = upper_bound - lower_bound
    int cnt = upper_bound(a.begin(), a.end(), 4)
            - lower_bound(a.begin(), a.end(), 4);
    cout << cnt << endl; // 2
}
```

### 答えを二分探索する（典型パターン）

「○○ が可能な最大（最小）の X を求めよ」という問題に使える。

**判定関数が書ければ二分探索が使える条件**：

- 答えが単調（X が大きくなると ○○ しやすく / しにくくなる）

```cpp
// テンプレート：「条件を満たす最大の x を求める」
long long lo = 0, hi = 1e9; // 答えの範囲
while (lo < hi) {
    long long mid = (lo + hi + 1) / 2; // 上に寄せる（最大を求めるとき）
    if (check(mid)) {
        lo = mid;       // mid が OK → もっと大きくできるか試す
    } else {
        hi = mid - 1;   // mid が NG → 小さくする
    }
}
cout << lo << endl;

// 「条件を満たす最小の x を求める」
long long lo = 0, hi = 1e9;
while (lo < hi) {
    long long mid = (lo + hi) / 2;  // 下に寄せる（最小を求めるとき）
    if (check(mid)) {
        hi = mid;       // mid が OK → もっと小さくできるか試す
    } else {
        lo = mid + 1;   // mid が NG → 大きくする
    }
}
cout << lo << endl;
```

### 例題：N 個の仕事を K 人で分担（最大値の最小化）

```
K 人でそれぞれ連続した区間を担当。各人の仕事量の最大値を最小化せよ。
→「最大値が mid 以下にできるか？」を判定
```

```cpp
auto check = [&](ll mid) -> bool {
    int people = 1;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur + a[i] > mid) { people++; cur = 0; }
        cur += a[i];
    }
    return people <= k;
};
```

---

## 2-3. しゃくとり法（Two Pointers）

### 発想

「連続する部分配列で条件を満たすものを探す」問題。
左端 `l`、右端 `r` の2つのポインタを使い、合計 O(N) で解く。

### 条件

- 要素がすべて**非負**（右端を伸ばすと単調増加）

### テンプレート

```cpp
// 「合計が K 以下の最長連続部分列」を求める例
int l = 0;
ll sum = 0;
int ans = 0;
for (int r = 0; r < n; r++) {
    sum += a[r];              // r を右に伸ばす
    while (sum > K) {
        sum -= a[l];          // 条件を破ったら l を縮める
        l++;
    }
    ans = max(ans, r - l + 1);
}
```

### 注意点

- l は右にしか進まない（合計 O(N)）
- 要素に負があると単調性が崩れるので使えない
- 「合計が K **以上**の最短」も同様に解ける

```cpp
// 「合計が K 以上の最短連続部分列」
int l = 0;
ll sum = 0;
int ans = INT_MAX;
for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum >= K) {
        ans = min(ans, r - l + 1);
        sum -= a[l++];
    }
}
```

---

## まとめ

| テクニック | 使う状況 | 計算量 |
| --- | --- | --- |
| 累積和 | 区間の合計を何度も求める | 構築 O(N), クエリ O(1) |
| `lower_bound` | ソート済み配列で値を探す | O(log N) |
| 答えを二分探索 | 単調な条件の最大/最小を求める | O(N log N) など |
| しゃくとり法 | 非負の連続部分列の条件を探す | O(N) |

---

## 練習問題

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC125B - Resale](https://atcoder.jp/contests/abc125/tasks/abc125_b) | 累積和の考え方 | ★☆☆ |
| [ABC130D - Enough Array](https://atcoder.jp/contests/abc130/tasks/abc130_d) | 累積和 + 二分探索 | ★★☆ |
| [ABC143C - Slimes](https://atcoder.jp/contests/abc143/tasks/abc143_c) | しゃくとり法 | ★★☆ |
| [ABC174C - Rounding](https://atcoder.jp/contests/abc174/tasks/abc174_c) | 二分探索の考え方 | ★★☆ |
| [ABC146C - Buy an Integer](https://atcoder.jp/contests/abc146/tasks/abc146_c) | 答えを二分探索 | ★★★ |
| [ABC192D - Base n](https://atcoder.jp/contests/abc192/tasks/abc192_d) | 答えを二分探索 | ★★★ |
