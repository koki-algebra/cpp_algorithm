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

    // ここに解法を書く

    return 0;
}
```

- `#include <bits/stdc++.h>` : 全ヘッダをまとめてインクルード
- `ios::sync_with_stdio(false); cin.tie(nullptr);` : 入出力を高速化（大量入力時に必須）

---

## 1-3. vector

配列の代わりに使う。サイズが可変で便利。

```cpp
int main() {
    // 宣言
    vl a = {3, 1, 4, 1, 5};  // vector<ll> の別名
    vl b(5, 0);               // 長さ5、全要素0
    vl c(5);                  // 長さ5（値は不定）

    // 要素アクセス
    cout << a[0] << endl;     // 3
    a.push_back(9);           // 末尾に追加
    cout << a.size() << endl; // 6

    // rep マクロ（0-indexed で n 回ループ）
    rep(i, a.size()) {
        cout << a[i] << " ";
    }
    cout << endl;

    // rep2 マクロ（a 以上 b 未満）
    rep2(i, 1, 4) {
        cout << a[i] << " "; // 1 4 1
    }
    cout << endl;

    return 0;
}
```

**`rep` の内部**：`for (ll i = 0; i < (ll)(n); i++)` に展開される。
`ll` で回すので `(int)a.size()` のキャストは不要。

---

## 1-4. sort

```cpp
int main() {
    vl a = {3, 1, 4, 1, 5, 9, 2, 6};

    // 昇順ソート（all マクロで begin/end を省略）
    sort(all(a));
    // a = {1, 1, 2, 3, 4, 5, 6, 9}

    // 降順ソート（rall マクロ）
    sort(rall(a));
    // a = {9, 6, 5, 4, 3, 2, 1, 1}

    return 0;
}
```

`sort` の計算量は $O(N \log N)$。

---

## 1-5. pair と tuple

複数の値をまとめて扱うときに使う。

```cpp
int main() {
    // pll は pair<ll, ll> の別名
    pll p = {3, 5};
    cout << p.first << " " << p.second << endl; // 3 5

    // pair のソート（first が優先、同じなら second）
    vector<pll> v = {{3, 2}, {1, 5}, {3, 1}};
    sort(all(v));
    // {{1,5}, {3,1}, {3,2}}

    // tuple（3つ以上）
    tuple<ll, ll, ll> t = {1, 2, 3};
    cout << get<0>(t) << endl; // 1

    return 0;
}
```

---

## 1-6. string

```cpp
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

## 1-7. 型エイリアスとマクロの一覧

テンプレートで定義済みの省略記法をまとめます。

### 型エイリアス

| 別名 | 実際の型 | 用途 |
| --- | --- | --- |
| `ll` | `long long` | 大きな整数 |
| `ull` | `unsigned long long` | 符号なし大整数 |
| `pll` | `pair<ll, ll>` | 2値のペア |
| `vl` | `vector<ll>` | 1次元配列 |
| `vvl` | `vector<vector<ll>>` | 2次元配列 |

### マクロ

| マクロ | 展開後 | 使い方 |
| --- | --- | --- |
| `rep(i, n)` | `for (ll i = 0; i < n; i++)` | 0〜n-1 のループ |
| `rep2(i, a, b)` | `for (ll i = a; i < b; i++)` | a〜b-1 のループ |
| `all(v)` | `v.begin(), v.end()` | sort などに渡す |
| `rall(v)` | `v.rbegin(), v.rend()` | 逆順 sort に渡す |

### 定数

```cpp
const ll INF = 1e18;    // 到達不能・未初期化の印（ll の最大値より小さい）
const ll MOD = 1e9 + 7; // 余りを取る問題で使う素数
```

**`int` か `ll` か**：$N \leq 10^5$ で $N^2$ を計算すると $10^{10}$ → `int`（最大 $\approx 2 \times 10^9$）ではオーバーフロー → `ll` を使う。

---

## まとめ

| 操作 | 計算量 | コード |
| --- | --- | --- |
| vector アクセス | $O(1)$ | `a[i]` |
| vector 末尾追加 | $O(1)$ | `a.push_back(x)` |
| sort | $O(N \log N)$ | `sort(all(a))` |

---

## 練習問題

以下の問題を解いてみましょう。

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC086A - Product](https://atcoder.jp/contests/abc086/tasks/abc086_a) | 基本操作 | ★☆☆ |
| [ABC081B - Shift only](https://atcoder.jp/contests/abc081/tasks/abc081_b) | ループ | ★☆☆ |
| [ABC088B - Grid](https://atcoder.jp/contests/abc088/tasks/abc088_b) | sort + 判定 | ★★☆ |
