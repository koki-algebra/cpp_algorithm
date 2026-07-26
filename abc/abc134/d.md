# ABC134 D - Preparing Boxes

- 問題: <https://atcoder.jp/contests/abc134/tasks/abc134_d>

## 問題の言い換え

- $N$ 個の空の箱が並んでおり、$i$ 番目の箱には整数 $i$ が書かれている($1 \le i \le N$)。
- 各箱についてボールを入れるか入れないかを選ぶ。箱 $i$ にボールを入れるかどうかを $x_i \in \{0, 1\}$ とする。
- 次の条件を満たす配置を1つ求めよ(存在しなければ `-1`)。

$$\sum_{i \mid j} x_j \equiv a_i \pmod 2 \quad (1 \le i \le N)$$

すなわち「$i$ の倍数番目の箱に入っているボールの個数の偶奇が $a_i$ と一致する」こと。

## 解法の考え方

$i$ に関する式を書き下すと

$$x_i + x_{2i} + x_{3i} + \cdots \equiv a_i \pmod 2$$

この式には「$x_i$ 自身」と「$i$ より**大きい**添字 $x_{2i}, x_{3i}, \dots$」しか現れない。

そこで $i = N, N-1, \dots, 1$ の順(大きい方から)に $x_i$ を決めていく。$i$ を処理する時点で $x_{2i}, x_{3i}, \dots$ はすでに確定しているので、

$$x_i = a_i \oplus (x_{2i} \oplus x_{3i} \oplus \cdots)$$

として一意に $x_i$ が定まる。

この操作を全ての $i$ に対して行えば、全ての制約式を満たす $x$ が必ず一意に構成できる(各方程式の対角成分が1の上三角行列を $\mathrm{GF}(2)$ 上で解いていることに相当するため、常に解が存在し、しかも一意)。したがって、この問題では実は `-1` を出力するケースは存在しない。

## 実装イメージ

`template.cpp` で定義済みの include・using・マクロは省略。

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    vl a(n + 1);
    rep2(i, 1, n + 1) cin >> a[i];

    vl x(n + 1, 0);
    for (ll i = n; i >= 1; i--) {
        ll cnt = 0;
        for (ll j = 2 * i; j <= n; j += i) cnt ^= x[j];
        x[i] = a[i] ^ cnt;
    }

    vl ans;
    rep2(i, 1, n + 1) if (x[i]) ans.push_back(i);

    cout << ans.size() << "\n";
    rep(i, ans.size()) cout << ans[i] << " \n"[i + 1 == (ll)ans.size()];

    return 0;
}
```

## 計算量

各 $i$ について $x_{2i}, x_{3i}, \dots$ を調べる回数は $\lfloor N/i \rfloor - 1$ 回程度。全体では

$$\sum_{i=1}^{N} \frac{N}{i} = O(N \log N)$$

(調和級数)となり、$N \le 2 \times 10^5$ でも十分高速($2 \times 10^5 \times \log(2\times10^5) \approx 2.4 \times 10^6$ 回程度)。

## 検証(サンプル1: $N=3,\ a=(1,0,0)$)

- $i=3$: 倍数なし → $x_3 = a_3 \oplus 0 = 0$
- $i=2$: 倍数なし($4>3$)→ $x_2 = a_2 \oplus 0 = 0$
- $i=1$: $x_2 \oplus x_3 = 0$ → $x_1 = a_1 \oplus 0 = 1$

結果 $x = (1, 0, 0)$ → 出力 `1` / `1`。サンプル出力と一致する。

## 注意点

- 解の一意性が保証されているため、上記の構成をそのまま実装すれば正しい解が得られる(不可能判定は不要で、常に `-1` にはならない)。
- $M = 0$(ボールを入れる箱がない)場合、最後の出力行が空行になる点に注意。
