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
    rep(i, n) cin >> a[i];

    // 累積和の構築
    vector<ll> S(n + 1, 0);
    rep(i, n) {
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
rep(i, H)
    rep(j, W)
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
    auto it = lower_bound(all(a), 4);
    cout << (it - a.begin()) << endl; // 2

    // upper_bound: x より大きい最初の位置
    auto it2 = upper_bound(all(a), 4);
    cout << (it2 - a.begin()) << endl; // 4

    // x が含まれる個数 = upper_bound - lower_bound
    int cnt = upper_bound(all(a), 4)
            - lower_bound(all(a), 4);
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

「最大値をできるだけ小さくする分け方」を直接探すのは難しい。そこで視点を変え、判定問題に言い換える。

> 各人の仕事量が `mid` 以下になるように、K 人以下で分割できるか？

**単調性の確認**：`mid` を大きくするほど1人あたり多く担当できる → 必要な人数は減る（Yes になりやすい）。
`mid` を小さくするほど必要な人数は増える（No になりやすい）。
→ `mid` に対して判定結果が単調に切り替わるので、二分探索で「Yes になる最小の mid」を探せる。それが答え。

#### 判定関数（貪欲法）

```cpp
auto check = [&](ll mid) -> bool {
    int people = 1;   // 最初の1人から始める
    ll cur = 0;       // 今担当している人の合計
    rep(i, n) {
        if (cur + a[i] > mid) {  // これ以上乗せると mid を超える
            people++;             // 次の人にバトンタッチ
            cur = 0;
        }
        cur += a[i];
    }
    return people <= k;  // 使った人数が K 人以内に収まったか
};
```

先頭から「今の人にまだ乗せられるなら乗せる、乗せられないなら次の人に切り替える」を繰り返すだけの貪欲法。
一人が担当する区間はできるだけ伸ばした方が後ろの要素に余裕ができて総人数を減らせるので、この貪欲は最適。

**トレース例**：`a = [3, 1, 4, 1, 5, 9, 2, 6]`、`mid = 14`

| i | a[i] | cur + a[i] | 判定 | 結果 |
| --- | --- | --- | --- | --- |
| 0 | 3 | 0+3=3 | ≤14 | cur=3 |
| 1 | 1 | 3+1=4 | ≤14 | cur=4 |
| 2 | 4 | 4+4=8 | ≤14 | cur=8 |
| 3 | 1 | 8+1=9 | ≤14 | cur=9 |
| 4 | 5 | 9+5=14 | ≤14 | cur=14 |
| 5 | 9 | 14+9=23 | >14 | people=2, cur=9 |
| 6 | 2 | 9+2=11 | ≤14 | cur=11 |
| 7 | 6 | 11+6=17 | >14 | people=3, cur=6 |

最終 `people = 3`。`K = 3` なら `check(14) = true`（`[3,1,4,1,5][9,2][6]` の合計は `14, 11, 6` で最大値14が達成可能）。

#### 二分探索本体

`check` だけでは完結しない。答えの探索範囲 `[lo, hi]` を決めて、2-2節のテンプレート通りに二分探索する。

```cpp
ll lo = *max_element(all(a));    // 下限：1人1要素でも a[i] は必要
ll hi = accumulate(all(a), 0LL); // 上限：1人で全部担当する場合

while (lo < hi) {
    ll mid = (lo + hi) / 2;
    if (check(mid)) {
        hi = mid;       // mid で足りる → もっと小さくできるか試す
    } else {
        lo = mid + 1;   // mid では足りない → 大きくする
    }
}
cout << lo << endl; // 答え
```

- **下限 `lo`**：どの人も少なくとも1要素は担当するので、`mid` が配列中の最大要素未満だと必ずオーバーする人が出てしまう。
- **上限 `hi`**：全要素の合計。1人にすべて担当させれば K=1 人以内で必ず収まる。

**計算量**：`check` が $O(N)$、二分探索が $O(\log(\text{sum}))$ 回 → 全体 $O(N \log(\text{sum}))$。

#### この形の見分け方

以下がすべて揃えば「答えを二分探索」パターンを疑う。

```
1. 「○○ができる最大/最小の X」という問い方をしている
2. X が大きい（小さい）ほど条件を満たしやすい/満たしにくい（単調性がある）
3. 「X 以下（以上）で条件を満たせるか？」という判定を O(N) 程度で書ける
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
rep(r, n) {
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
rep(r, n) {
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
| [ABC130D - Enough Array](https://atcoder.jp/contests/abc130/tasks/abc130_d) | 累積和 + 二分探索 | ★★☆ |
| [ABC143C - Slimes](https://atcoder.jp/contests/abc143/tasks/abc143_c) | しゃくとり法 | ★★☆ |
| [ABC174C - Rounding](https://atcoder.jp/contests/abc174/tasks/abc174_c) | 二分探索の考え方 | ★★☆ |
| [ABC146C - Buy an Integer](https://atcoder.jp/contests/abc146/tasks/abc146_c) | 答えを二分探索 | ★★★ |
| [ABC192D - Base n](https://atcoder.jp/contests/abc192/tasks/abc192_d) | 答えを二分探索 | ★★★ |
