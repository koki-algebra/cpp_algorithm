# 第6章：数学

---

## 6-1. 剰余（mod）演算

### なぜ mod が必要か

答えが非常に大きくなる問題では「$10^9 + 7$ で割った余りを答えよ」という形式が多い。

**ルール**：加算・乗算は mod を取る前でも後でも同じ結果になる。

$$
(a + b) \bmod m = ((a \bmod m) + (b \bmod m)) \bmod m
$$

$$
(a \times b) \bmod m = ((a \bmod m) \times (b \bmod m)) \bmod m
$$

```cpp
const long long MOD = 1e9 + 7;

long long add(long long a, long long b) {
    return (a + b) % MOD;
}

long long mul(long long a, long long b) {
    return (a % MOD) * (b % MOD) % MOD;
}
```

**注意**：引き算は負になる可能性があるため `+MOD` してから mod を取る。

```cpp
long long sub(long long a, long long b) {
    return ((a - b) % MOD + MOD) % MOD;
}
```

---

## 6-2. 冪乗（繰り返し二乗法）

### 問題

$a^n \bmod m$ を $O(\log n)$ で計算する。

### 仕組み

$$
a^n = \begin{cases}
1 & (n = 0) \\
(a^{n/2})^2 & (n \text{ が偶数}) \\
a \cdot a^{n-1} & (n \text{ が奇数})
\end{cases}
$$

```cpp
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod; // 奇数のとき
        base = base * base % mod;
        exp >>= 1; // exp を 2 で割る
    }
    return result;
}

// 使い方
long long ans = power(2, 60, MOD); // 2^60 mod (10^9+7)
```

---

## 6-3. GCD と LCM

### GCD（最大公約数）

ユークリッドの互除法を使うと $O(\log \min(a, b))$ で求まる。

$$
\gcd(a, b) = \gcd(b, a \bmod b)
$$

```cpp
// C++17 では __gcd または std::gcd が使える
#include <numeric>
long long g = gcd(12, 8); // 4

// 自前で書く場合
long long my_gcd(long long a, long long b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}
```

### LCM（最小公倍数）

$$
\text{lcm}(a, b) = \frac{a \times b}{\gcd(a, b)}
$$

```cpp
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b; // オーバーフロー防止のため先に割る
}
```

---

## 6-4. 素数

### 判定：$O(\sqrt{N})$

```cpp
bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

### エラトステネスの篩：$O(N \log \log N)$

N 以下のすべての素数を列挙する。

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

### 素因数分解：$O(\sqrt{N})$

```cpp
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> factors;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) { n /= i; cnt++; }
            factors.push_back({i, cnt});
        }
    }
    if (n > 1) factors.push_back({n, 1});
    return factors;
}

// 12 = 2^2 × 3 → {{2,2}, {3,1}}
```

---

## 6-5. 組み合わせ（mod 演算）

### $_nC_k$ の計算

$$
{}_nC_k = \frac{n!}{k! \cdot (n-k)!}
$$

mod の下で割り算をするには**逆元**が必要。  
$p$ が素数のとき、フェルマーの小定理より：

$$
a^{-1} \equiv a^{p-2} \pmod{p}
$$

```cpp
const long long MOD = 1e9 + 7;
const int MAXN = 200005;

long long fact[MAXN], inv_fact[MAXN];

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    rep2(i, 1, MAXN) fact[i] = fact[i-1] * i % MOD;
    inv_fact[MAXN-1] = power(fact[MAXN-1], MOD - 2, MOD);
    for (int i = MAXN-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] % MOD * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

int main() {
    precompute();
    cout << comb(10, 3) << endl; // 120
}
```

---

## 6-6. よく使う数学的性質

### 約数の個数

$N$ の約数の個数は平均的に $O(\log N)$、最悪でも $N^{0.3}$ 程度。

```cpp
vector<int> divisors(int n) {
    vector<int> divs;
    for (int i = 1; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    sort(all(divs));
    return divs;
}
```

### ビット演算

| 操作 | 記法 | 意味 |
| --- | --- | --- |
| AND | `a & b` | 両方 1 のビットのみ 1 |
| OR | `a \| b` | どちらか 1 のビットが 1 |
| XOR | `a ^ b` | 異なるビットが 1 |
| 左シフト | `a << k` | $a \times 2^k$ |
| 右シフト | `a >> k` | $a \div 2^k$ |
| k ビット目が立っているか | `(a >> k) & 1` | 0 か 1 |

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

---

## まとめ

| テーマ | 計算量 | 使う場面 |
| --- | --- | --- |
| mod 演算 | $O(1)$ | 答えが大きくなる問題 |
| 繰り返し二乗法 | $O(\log n)$ | $a^n \bmod m$ |
| GCD | $O(\log \min(a,b))$ | 公約数・公倍数 |
| 素数判定 | $O(\sqrt{N})$ | 単一の素数判定 |
| エラトステネスの篩 | $O(N \log \log N)$ | 複数の素数列挙 |
| 組み合わせの前処理 | $O(N)$ | $_nC_k$ をたくさん計算 |

---

## 練習問題

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC180C - Cream puff](https://atcoder.jp/contests/abc180/tasks/abc180_c) | 約数列挙 | ★☆☆ |
| [ABC106B - 105](https://atcoder.jp/contests/abc106/tasks/abc106_b) | 素数・約数 | ★★☆ |
| [ABC134C - Exception Handling](https://atcoder.jp/contests/abc134/tasks/abc134_c) | GCD | ★★☆ |
| [ABC156D - Bouquet](https://atcoder.jp/contests/abc156/tasks/abc156_d) | 組み合わせ mod | ★★★ |
| [ABC214C - Distribution](https://atcoder.jp/contests/abc214/tasks/abc214_c) | GCD の応用 | ★★★ |
