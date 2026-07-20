# 第6章：数学

---

## 6-1. 剰余（mod）演算

### なぜ mod が必要か

競技プログラミングでは「答えを $10^9 + 7$ で割った余りを求めよ」という問題が頻出する。
これは、答えそのものが `ll`（約 $9.2 \times 10^{18}$ まで）に収まらないほど大きくなるため、割った余りだけを答えさせている。

途中の計算をすべて mod を取りながら進めないと、最終結果を出す前にオーバーフローしてしまう。
そこで「途中で mod を取っても最終的な余りは変わらない」という性質を利用する。

### なぜ mod を取っても結果が変わらないのか

$a = q_1 m + r_1$、$b = q_2 m + r_2$（$r_1, r_2$ が余り）とおくと、

$$
a + b = (q_1 + q_2) m + (r_1 + r_2)
$$

なので、両辺を $m$ で割った余りは $r_1 + r_2$ を $m$ で割った余りと一致する。乗算も同様に、

$$
a \times b = (q_1 m + r_1)(q_2 m + r_2) = m(\dots) + r_1 r_2
$$

となり、$m(\dots)$ の部分は $m$ で割り切れるので余りに影響しない。つまり、

$$
(a + b) \bmod m = ((a \bmod m) + (b \bmod m)) \bmod m
$$

$$
(a \times b) \bmod m = ((a \bmod m) \times (b \bmod m)) \bmod m
$$

が成り立つ。**加算と乗算は自由に mod を取ってよい**というのはこの理屈による。

```cpp
ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return (a % MOD) * (b % MOD) % MOD;
}
```

### 引き算の注意

C++ の `%` は負の数に対して負の余りを返しうる（例：`(-3) % 5 == -3`）。数学的な余り（$0$ 以上）にしたい場合は `+MOD` してから mod を取る。

```cpp
ll sub(ll a, ll b) {
    return ((a - b) % MOD + MOD) % MOD;
}
```

### 割り算は単純にできない

加減乗と違い、**割り算は mod を取ったまま計算できない**。

$$
(a \div b) \bmod m \neq ((a \bmod m) \div (b \bmod m)) \bmod m
$$

これは整数の世界に「割り算」という演算がそのままでは存在しない（割り切れるとは限らない）ため。
mod の世界で割り算をするには、$b$ の**逆元**（$b \times b^{-1} \equiv 1 \pmod m$ となる $b^{-1}$）を求め、割り算を「逆元を掛ける」操作に置き換える必要がある（→ 6-5節）。

---

## 6-2. 冪乗（繰り返し二乗法）

### 問題

$a^n \bmod m$ を計算したい。単純に `for` ループで $a$ を $n$ 回掛けると $O(n)$ かかり、$n$ が $10^9$ を超えるような問題では間に合わない。**繰り返し二乗法**（binary exponentiation）を使うと $O(\log n)$ で計算できる。

### 仕組み

指数 $n$ を再帰的に半分にしていく。

$$
a^n = \begin{cases}
1 & (n = 0) \\
(a^{n/2})^2 & (n \text{ が偶数}) \\
a \cdot a^{n-1} & (n \text{ が奇数})
\end{cases}
$$

これは、指数 $n$ を2進数展開したときの各ビットに対応していると考えるとわかりやすい。$n$ を2進数で $n = b_k b_{k-1} \cdots b_1 b_0$ と表すと、

$$
n = \sum_{i} b_i \cdot 2^i \quad \Longrightarrow \quad a^n = \prod_{i:\, b_i = 1} a^{2^i}
$$

つまり、$a, a^2, a^4, a^8, \dots$（底を繰り返し2乗した値）のうち、$n$ の2進数表記で1が立っている桁に対応するものだけを掛け合わせれば $a^n$ が得られる。

### 具体例：$3^{13}$ を計算する

$13 = 1101_{(2)} = 8 + 4 + 1$ なので、

$$
3^{13} = 3^8 \times 3^4 \times 3^1
$$

| $i$ | ビット | 底 $a^{2^i}$ | 掛けるか |
| --- | --- | --- | --- |
| 0 | 1 | $3^1 = 3$ | ○ |
| 1 | 0 | $3^2 = 9$ | × |
| 2 | 1 | $3^4 = 81$ | ○ |
| 3 | 1 | $3^8 = 6561$ | ○ |

$3 \times 81 \times 6561 = 1594323 = 3^{13}$ と一致する。

### 実装

```cpp
ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod; // 奇数のとき（そのビットが1）
        base = base * base % mod;                  // 底を2乗する
        exp >>= 1;                                 // exp を 2 で割る（次のビットへ）
    }
    return result;
}

// 使い方
ll ans = power(2, 60, MOD); // 2^60 mod (10^9+7)
```

`exp & 1` で最下位ビットを確認し、そのビットが1なら答えに掛ける。`base = base * base` で底を2乗し続け、`exp >>= 1` で見るビットを1つずつ進める。ループは $\log_2 n$ 回で終わるので、全体で $O(\log n)$。

### 計算量

- 通常の累乗計算：$O(n)$
- 繰り返し二乗法：$O(\log n)$

### 応用

- 逆元計算（フェルマーの小定理、→ 6-5節）
- 行列累乗（漸化式の高速計算、フィボナッチ数列の $n$ 項目を $O(\log n)$ で求める等）

---

## 6-3. GCD と LCM

### GCD（最大公約数）とユークリッドの互除法

$\gcd(a, b)$ を求めるのに、$1$ から $\min(a,b)$ まで全部試すと $O(\min(a,b))$ かかる。ユークリッドの互除法を使うと $O(\log \min(a, b))$ まで落とせる。

$$
\gcd(a, b) = \gcd(b, a \bmod b)
$$

**なぜ成り立つか**：$a = qb + r$（$r = a \bmod b$）とおく。$a$ と $b$ の公約数を $d$ とすると、$r = a - qb$ も $d$ で割り切れる。逆に $b$ と $r$ の公約数を $d'$ とすると、$a = qb + r$ も $d'$ で割り切れる。つまり「$a, b$ の公約数の集合」と「$b, r$ の公約数の集合」は完全に一致するので、最大公約数も一致する。

### 具体例：$\gcd(48, 18)$

```
gcd(48, 18) = gcd(18, 48 % 18) = gcd(18, 12)
gcd(18, 12) = gcd(12, 18 % 12) = gcd(12, 6)
gcd(12, 6)  = gcd(6, 12 % 6)   = gcd(6, 0)
gcd(6, 0)   = 6   ← b が 0 になったら a が答え
```

$b=0$ になったら $a$ を返す、というのが再帰の終了条件。

```cpp
// C++17 では __gcd または std::gcd が使える
ll g = gcd(12, 8); // 4

// 自前で書く場合（非再帰）
ll my_gcd(ll a, ll b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}
```

**計算量が $O(\log \min(a,b))$ になる理由**：$a \bmod b < a / 2$（$b \le a/2$ なら明らかに $a \bmod b < b \le a/2$、$b > a/2$ なら $a \bmod b = a - b < a/2$）が成り立つため、2ステップ進むごとに値が半分以下になる。よって反復回数は $O(\log(\min(a,b)))$。

### LCM（最小公倍数）

$$
\text{lcm}(a, b) = \frac{a \times b}{\gcd(a, b)}
$$

```cpp
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b; // オーバーフロー防止のため先に割る
}
```

**先に `a / gcd(a, b)` を計算する理由**：`a * b` を先に計算すると、$a, b$ が大きいときに `ll` の範囲（約 $9.2 \times 10^{18}$）を超えてオーバーフローする危険がある。`a / gcd(a, b)` は必ず割り切れる（$\gcd(a,b)$ は $a$ の約数）ので、先に割ってから掛けることで最終結果に近い大きさまで値を抑えられる。

---

## 6-4. 素数

### 判定：$O(\sqrt{N})$ で十分な理由

$N$ が素数かどうかを $2$ から $N-1$ まで全部試すと $O(N)$ かかるが、$\sqrt{N}$ まで試せば十分。

**理由**：もし $N = a \times b$（$a \le b$）と分解できるなら、$a \le \sqrt{N} \le b$ が必ず成り立つ（$a > \sqrt{N}$ かつ $b > \sqrt{N}$ だと $a \times b > N$ になり矛盾）。つまり、$N$ が合成数なら $\sqrt{N}$ 以下に必ず約数が見つかるので、$\sqrt{N}$ まで調べて約数が見つからなければ素数だと判定できる。

```cpp
bool is_prime(ll n) {
    if (n <= 1) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

### エラトステネスの篩：$O(N \log \log N)$

**複数の**素数を一気に列挙したいとき、1個ずつ `is_prime` を呼ぶと $O(N \sqrt{N})$ かかってしまう。エラトステネスの篩は「素数 $p$ の倍数を全部消していく」ことで、$N$ 以下のすべての素数を効率よく求める。

```
2 3 4 5 6 7 8 9 10 ...
2 は素数 → 4, 6, 8, 10, ... を消す
3 は素数 → 6, 9, 12, ... を消す（既に消えているものはそのまま）
4 は消えている → スキップ
5 は素数 → 10, 15, 20, ... を消す
...
消されずに残った数が素数
```

```cpp
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// 使い方
auto primes = sieve(1000000);
// primes[p] == true なら p は素数
```

**細かい工夫**：内側のループを `i * i` から始めているのは、$i \times k$（$k < i$）は既により小さい素数の倍数として消されているから。また外側のループが `i * i <= n` で止まるのも、素数判定と同じ理由（$\sqrt{N}$ 以下を調べれば十分）による。

**計算量が $O(N \log \log N)$ になる理由**：各素数 $p$ について、その倍数を消す回数は約 $N/p$ 回。全ての素数について合計すると

$$
\sum_{p \le N,\ p:\text{素数}} \frac{N}{p} = N \sum_{p \le N} \frac{1}{p} \approx N \log \log N
$$

（素数の逆数和が $\log \log N$ のオーダーで発散するという数論の結果による）。$N \log N$ よりもかなり小さく、$N$ に対してほぼ線形に近い。

### 素因数分解：$O(\sqrt{N})$

素数判定と同じ発想。$\sqrt{N}$ まで割ってみて、割り切れる数で割れるだけ割る。$\sqrt{N}$ より大きい素因数は最大1個しか残らない（2個以上あれば積が $N$ を超える）ので、ループの最後に `n > 1` かどうかで判定する。

```cpp
vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) { n /= i; cnt++; }
            factors.push_back({i, cnt});
        }
    }
    if (n > 1) factors.push_back({n, 1}); // sqrt(N) より大きい素因数が1個だけ残るケース
    return factors;
}

// 12 = 2^2 × 3 → {{2,2}, {3,1}}
```

---

## 6-5. 組み合わせ（mod 演算）

### $_nC_k$ の計算と逆元

$$
{}_nC_k = \frac{n!}{k! \cdot (n-k)!}
$$

6-1節で述べた通り、mod の世界では割り算をそのまま行えない。$b$ で割る代わりに、$b$ の**逆元** $b^{-1}$（$b \times b^{-1} \equiv 1 \pmod m$ を満たす数）を掛ける。

$$
\frac{a}{b} \bmod m = a \times b^{-1} \bmod m
$$

### フェルマーの小定理

$p$ が素数で $a$ が $p$ の倍数でないとき、

$$
a^{p-1} \equiv 1 \pmod{p}
$$

が成り立つ（フェルマーの小定理）。両辺を $a$ で割ると、

$$
a^{p-2} \equiv a^{-1} \pmod{p}
$$

つまり **$a^{p-2} \bmod p$ が $a$ の逆元になる**。これは6-2節の繰り返し二乗法を使えば $O(\log p)$ で計算できる。

```cpp
ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll inv(ll a, ll mod = MOD) {
    return power(a, mod - 2, mod); // mod が素数のときのみ有効
}
```

**注意**：この方法は $m$ が**素数**のときにしか使えない。$m$ が素数でない場合は拡張ユークリッドの互除法で逆元を求める必要がある。

### なぜ階乗を前計算するか

$_nC_k$ を求めるたびに逆元を計算すると、1回あたり $O(\log(\text{MOD}))$ かかる。クエリが $Q$ 回あると $O(Q \log(\text{MOD}))$ になってしまう。

そこで、階乗 `fact[i]` とその逆元 `inv_fact[i]` をあらかじめ $O(N)$ で前計算しておけば、各クエリは $O(1)$ で答えられる。

**逆元の前計算を $O(N)$ にする工夫**：`inv_fact[MAXN-1]` だけ繰り返し二乗法で求め（$O(\log(\text{MOD}))$）、そこから

$$
\text{inv\_fact}[i] = \text{inv\_fact}[i+1] \times (i+1) \bmod p
$$

を使って**逆向きに**計算する。これは $(i+1)! \times \text{inv\_fact}[i+1] \equiv 1$ の両辺に $(i+1)$ を掛けると $i! \times \text{inv\_fact}[i+1] \times (i+1) \equiv (i+1)$ となり、整理すると上の漸化式が導けることによる。逆元を1つずつ再計算するより高速。

```cpp
const int MAXN = 200005;

ll fact[MAXN], inv_fact[MAXN];

void precompute() {
    fact[0] = 1;
    rep2(i, 1, MAXN) fact[i] = fact[i-1] * i % MOD;
    inv_fact[MAXN-1] = power(fact[MAXN-1], MOD - 2, MOD);
    for (int i = MAXN-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] % MOD * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

// 使い方
precompute();
cout << comb(10, 3) << endl; // 120
```

**計算量**：前計算 $O(N)$（$N$ = 想定する $n$ の最大値）、各クエリ $O(1)$。

---

## 6-6. よく使う数学的性質

### 約数の個数と列挙

$N$ の約数は $\sqrt{N}$ 以下と $\sqrt{N}$ 以上のペアで現れる（$i \times (N/i) = N$）ので、$\sqrt{N}$ まで調べれば全列挙できる。個数は平均的に $O(\log N)$ 程度だが、約数の多い数（高度合成数）では最悪 $N^{0.3}$ 程度になる。

```cpp
vector<int> divisors(int n) {
    vector<int> divs;
    for (int i = 1; (ll)i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i); // i と n/i が同じ（n が平方数）場合は重複させない
        }
    }
    sort(all(divs));
    return divs;
}
```

### ビット演算

整数を2進数として扱う操作。集合の部分集合を表現したり（bit全探索）、高速な演算（乗除算の代わり）に使う。

| 操作 | 記法 | 意味 |
| --- | --- | --- |
| AND | `a & b` | 両方 1 のビットのみ 1 |
| OR | `a \| b` | どちらか 1 のビットが 1 |
| XOR | `a ^ b` | 異なるビットが 1 |
| 左シフト | `a << k` | $a \times 2^k$ |
| 右シフト | `a >> k` | $a \div 2^k$（切り捨て） |
| k ビット目が立っているか | `(a >> k) & 1` | 0 か 1 |
| 立っているビットの数 | `__builtin_popcount(a)` | ビットの1の個数 |

### bit 全探索

$N$ 個の要素それぞれについて「選ぶ／選ばない」の $2^N$ 通りを全部試したいとき、$0$ から $2^N - 1$ までの整数を「どの要素を選ぶか」を表すビット列とみなして全探索する。

```cpp
// N 以下の整数をビット全探索（2^N 通り）
rep(bit, 1 << n) {
    rep(i, n) {
        if ((bit >> i) & 1) {
            // i 番目の要素を選ぶ
        }
    }
}
```

`bit` の $i$ ビット目が1なら「$i$ 番目の要素を選んだ状態」を表す。$N \le 20$ 程度（$2^{20} \approx 10^6$）まで実用的。

---

## まとめ

| テーマ | 計算量 | 使う場面 |
| --- | --- | --- |
| mod 演算 | $O(1)$ | 答えが大きくなる問題 |
| 繰り返し二乗法 | $O(\log n)$ | $a^n \bmod m$、逆元計算 |
| GCD（ユークリッドの互除法） | $O(\log \min(a,b))$ | 公約数・公倍数 |
| 素数判定 | $O(\sqrt{N})$ | 単一の素数判定 |
| エラトステネスの篩 | $O(N \log \log N)$ | 複数の素数列挙 |
| 素因数分解 | $O(\sqrt{N})$ | 単一の数の素因数分解 |
| 組み合わせの前処理 | $O(N)$、各クエリ $O(1)$ | $_nC_k$ をたくさん計算 |
| 約数列挙 | $O(\sqrt{N})$ | 単一の数の約数列挙 |
| bit 全探索 | $O(2^N \times N)$ | $N \le 20$ 程度の部分集合探索 |

### 数学パートの思考フロー

```
答えが大きくなりそう？ → mod を意識する
        ↓
割り算が必要？ → 逆元（フェルマーの小定理 or 拡張ユークリッド）
        ↓
累乗の計算が必要？ → 繰り返し二乗法で O(log n)
        ↓
約数・倍数・素数が絡む？ → GCD／篩／素因数分解
        ↓
組み合わせを何度も計算？ → 階乗と逆元階乗を前計算
```

---

## 練習問題

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC180C - Cream puff](https://atcoder.jp/contests/abc180/tasks/abc180_c) | 約数列挙 | ★☆☆ |
| [ABC106B - 105](https://atcoder.jp/contests/abc106/tasks/abc106_b) | 素数・約数 | ★★☆ |
| [ABC134C - Exception Handling](https://atcoder.jp/contests/abc134/tasks/abc134_c) | GCD | ★★☆ |
| [ABC156D - Bouquet](https://atcoder.jp/contests/abc156/tasks/abc156_d) | 組み合わせ mod | ★★★ |
| [ABC214C - Distribution](https://atcoder.jp/contests/abc214/tasks/abc214_c) | GCD の応用 | ★★★ |
