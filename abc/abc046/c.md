# ABC046 C / ARC062 A - AtCoDeer and Election Report

- 問題: <https://atcoder.jp/contests/abc046/tasks/arc062_a>
- 参考: <https://drken1215.hatenablog.com/entry/2024/09/14/142332>

## 問題の言い換え

- 得票数の組 $(t, a)$ は $t=a=1$ からスタート。
- $i$ 回目の観測で「比が $T_i : A_i$」と分かる。$T_i, A_i$ は互いに素。
- 実際の得票 $(X, Y)$ は、**票数は減らない**($X \ge t,\ Y \ge a$)という条件のもとで、**あり得る最小の組**を採用する(最小得票数を答えたいので)。
- これを $N$ 回繰り返した後の $t + a$ が答え。

## 解説のキモ:比が一致する整数の組は何か

$T_i, A_i$ が互いに素なとき、比が $T_i : A_i$ になる正整数の組 $(X, Y)$ は、**必ず**

$$
X = T_i \cdot k,\quad Y = A_i \cdot k \quad (k \text{ は正整数})
$$

の形しかありません。たとえば $T_i:A_i = 2:3$ なら、$(2,3), (4,6), (6,9), \dots$ としか書けない。「互いに素」という条件がここで効いていて、これがないと $(X,Y)$ の形が一意に $k$ 倍で書けなくなります。

## $X \ge t,\ Y \ge a$ を $k$ の条件に翻訳する

- $X \ge t \iff T_i k \ge t \iff k \ge t / T_i \iff k \ge \lceil t / T_i \rceil$($k$は整数だから)
- 同様に $Y \ge a \iff k \ge \lceil a / A_i \rceil$

この2つの不等式を「同時に」満たす最小の $k$ が欲しいわけですが、2つの下限のうち大きい方さえ満たせば両方満たされるので、

$$
k = \max\left(\lceil t/T_i \rceil,\ \lceil a/A_i \rceil\right)
$$

が答えになります。「AND条件の最小値 = 各下限のmax」というだけの話です。

この $k$ を使って $t \leftarrow T_i k,\ a \leftarrow A_i k$ と更新し、これを $N$ 回繰り返します。

## 補足: $\lceil \cdot \rceil$ は天井関数(ガウス記号=床関数ではない)

$\lceil x \rceil$(天井関数, ceiling)と $\lfloor x \rfloor$(床関数, floor。日本の高校数学で言う「ガウス記号 $[x]$」はこちら)は向きが逆なので注意。

- 床関数(ガウス記号) $\lfloor x \rfloor$: $x$ 以下の**最大**の整数。例: $\lfloor 1/2 \rfloor = 0$
- 天井関数 $\lceil x \rceil$: $x$ 以上の**最小**の整数。例: $\lceil 1/2 \rceil = 1$

ここで欲しいのは「$k \ge t/T_i$ を満たす最小の整数 $k$」。

- $t/T_i$ がちょうど整数なら、その値自身が答え。
- 整数でないなら、**切り上げた**値が答え。切り捨てると $k < t/T_i$ になり $X = T_i k \ge t$ を満たさなくなる。

例えば $t=1, T_i=2$ なら $t/T_i = 0.5$。床関数だと $\lfloor 0.5 \rfloor = 0 \Rightarrow X = 0 < 1$ で条件違反。天井関数なら $\lceil 0.5 \rceil = 1 \Rightarrow X = 2 \ge 1$ で条件を満たす。だから切り上げ(天井関数)でなければならない。

C++の整数除算 `a / b` は(正の数同士なら)切り捨て、つまり床関数の動きをする。天井関数を作るには、正の整数 $a, b$ に対して成り立つ等式

$$
\lceil a/b \rceil = \left\lfloor \frac{a+b-1}{b} \right\rfloor
$$

を使い、`(a + b - 1) / b` と書けば天井除算になる。

## 具体例でトレース

$N=3$、観測が $(2,3), (1,1), (3,2)$ の場合:

| ステップ | $T,A$ | $\lceil t/T\rceil$ | $\lceil a/A\rceil$ | $k$ | 新しい $(t,a)$ |
| --- | --- | --- | --- | --- | --- |
| 初期 | - | - | - | - | $(1,1)$ |
| 1 | $2,3$ | $\lceil1/2\rceil=1$ | $\lceil1/3\rceil=1$ | $1$ | $(2,3)$ |
| 2 | $1,1$ | $\lceil2/1\rceil=2$ | $\lceil3/1\rceil=3$ | $3$ | $(3,3)$ |
| 3 | $3,2$ | $\lceil3/3\rceil=1$ | $\lceil3/2\rceil=2$ | $2$ | $(6,4)$ |

答えは $t+a = 10$。各ステップで「比を保ちつつ両方が減らないための最小限の水増し」をしているのが見て取れる。

## 実装上の注意点(オーバーフロー)

$T_i, A_i$ は最大 $10^9$ 程度、答えは $10^{18}$ 以下まで許容されているので、$T_i \cdot k$ の計算途中でオーバーフローしないよう `long long`(できれば範囲チェックや `__int128`)で計算する必要がある。
