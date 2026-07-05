# 第1章：計算量と STL 基礎

## 1-1. 計算量（Big O 記法）

### なぜ計算量を学ぶのか

AtCoder の制約には `N ≤ 2×10^5` のような数字が書いてあります。
計算量を理解すると「この解法は間に合うか？」を瞬時に判断できます。

### 目安：1秒で処理できる演算数 $\approx 10^8$

| 制約 $N$ | 許容される計算量 | 典型アルゴリズム |
| --- | --- | --- |
| $N \leq 10^8$ | $O(N)$ | 単純な一重ループ |
| $N \leq 10^6$ | $O(N \log N)$ | ソート、二分探索 |
| $N \leq 3000$ | $O(N^2)$ | 二重ループ |
| $N \leq 300$ | $O(N^3)$ | 三重ループ |
| $N \leq 20$ | $O(2^N)$ | 全探索（ビット全探索） |

### よく出る計算量の感覚

$$O(1) < O(\log N) < O(N) < O(N \log N) < O(N^2) < O(2^N)$$

定数時間 < 対数時間 < 線形 < 線形×対数 < 二乗 < 指数

**$\log N$ の感覚**：$N = 10^5$ のとき $\log_2 N \approx 17$

### 問題を見たときのチェックフロー

```
制約を見る
  → N ≤ 2×10^5 なら O(N log N) 以下が必要
  → 二重ループ（O(N²) = 4×10^10）は絶対TLE
```

---

## 1-2. C++ 競プロ基本テンプレート

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ここに解法を書く

    return 0;
}
```

- `#include <bits/stdc++.h>` : 全ヘッダをまとめてインクルード
- `ios_base::sync_with_stdio(false); cin.tie(NULL);` : 入出力を高速化（大量入力時に必須）

---

## 1-3. vector

配列の代わりに使う。サイズが可変で便利。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 宣言
    vector<int> a = {3, 1, 4, 1, 5};
    vector<int> b(5, 0);    // 長さ5、全要素0
    vector<int> c(5);       // 長さ5（値は不定）

    // 要素アクセス
    cout << a[0] << endl;   // 3
    a.push_back(9);         // 末尾に追加
    cout << a.size() << endl; // 6

    // 範囲 for
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;

    // インデックス付き for
    for (int i = 0; i < (int)a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
```

**注意**：`a.size()` は `unsigned` 型なので、`int` とループ比較するときは `(int)a.size()` とキャストする。

---

## 1-4. sort

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};

    // 昇順ソート
    sort(a.begin(), a.end());
    // a = {1, 1, 2, 3, 4, 5, 6, 9}

    // 降順ソート
    sort(a.begin(), a.end(), greater<int>());
    // a = {9, 6, 5, 4, 3, 2, 1, 1}

    return 0;
}
```

`sort` の計算量は **O(N log N)**。

---

## 1-5. pair と tuple

複数の値をまとめて扱うときに使う。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // pair
    pair<int, int> p = {3, 5};
    cout << p.first << " " << p.second << endl; // 3 5

    // pair のソート（first が優先、同じなら second）
    vector<pair<int, int>> v = {{3, 2}, {1, 5}, {3, 1}};
    sort(v.begin(), v.end());
    // {{1,5}, {3,1}, {3,2}}

    // tuple（3つ以上）
    tuple<int, int, int> t = {1, 2, 3};
    cout << get<0>(t) << endl; // 1

    return 0;
}
```

---

## 1-6. string

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "hello";
    cout << s.size() << endl;   // 5
    cout << s[1] << endl;       // e
    s += " world";              // 連結
    cout << s << endl;          // hello world

    // 部分文字列
    cout << s.substr(6, 5) << endl; // world（6文字目から5文字）

    // 文字→数字変換
    char c = '5';
    int n = c - '0';  // n = 5

    return 0;
}
```

---

## 1-7. 型エイリアスとよく使うマクロ

```cpp
#include <bits/stdc++.h>
using namespace std;

// long long を ll と書けるようにする
using ll = long long;

// よく使う定数
const ll INF = 1e18;   // 無限大（long long の最大値より小さい）
const int MOD = 1e9 + 7;

int main() {
    ll a = 1e18;  // 10^18
    // int の最大値は約 2×10^9 → N×N を計算するなら ll が必要
    return 0;
}
```

**`int` か `ll` か**：$N \leq 10^5$ で $N^2$ を計算すると $10^{10}$ → `int` だとオーバーフロー → `ll` を使う。

---

## まとめ

| 操作 | 計算量 | コード |
| --- | --- | --- |
| vector アクセス | O(1) | `a[i]` |
| vector 末尾追加 | O(1) | `a.push_back(x)` |
| sort | O(N log N) | `sort(a.begin(), a.end())` |

---

## 練習問題

以下の問題を解いてみましょう。

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC086A - Product](https://atcoder.jp/contests/abc086/tasks/abc086_a) | 基本操作 | ★☆☆ |
| [ABC081B - Shift only](https://atcoder.jp/contests/abc081/tasks/abc081_b) | ループ | ★☆☆ |
| [ABC088B - Grid](https://atcoder.jp/contests/abc088/tasks/abc088_b) | sort + 判定 | ★★☆ |
| [ABC128C - Switches](https://atcoder.jp/contests/abc128/tasks/abc128_c) | 全探索 + sort | ★★☆ |
