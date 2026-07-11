# 第3章：データ構造

「適切なデータ構造を選ぶ」だけで解法が劇的にシンプルになります。

---

## 3-1. Stack（スタック）

LIFO（Last In, First Out）：最後に入れたものを最初に取り出す。

### 使う場面

- 括弧の対応チェック
- 直前の大きい/小さい要素を探す（単調スタック）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<int> st;
    st.push(1);   // 追加
    st.push(2);
    st.push(3);
    cout << st.top() << endl;  // 3（先頭を見る）
    st.pop();                  // 先頭を削除
    cout << st.top() << endl;  // 2
    cout << st.size() << endl; // 2
    cout << st.empty() << endl; // 0（空でない）
}
```

### 括弧チェックの例

```cpp
// "(()())" のような文字列が正しく対応しているか判定
string s;
cin >> s;
stack<char> st;
bool ok = true;
for (char c : s) {
    if (c == '(') {
        st.push(c);
    } else {
        if (st.empty()) { ok = false; break; }
        st.pop();
    }
}
if (!st.empty()) ok = false;
cout << (ok ? "YES" : "NO") << endl;
```

---

## 3-2. Queue（キュー）

FIFO（First In, First Out）：最初に入れたものを最初に取り出す。
BFS（幅優先探索）で使う（第4章参照）。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    queue<int> q;
    q.push(1);   // 末尾に追加
    q.push(2);
    q.push(3);
    cout << q.front() << endl; // 1（先頭を見る）
    q.pop();                   // 先頭を削除
    cout << q.front() << endl; // 2
}
```

---

## 3-3. Priority Queue（優先度付きキュー / ヒープ）

常に最大値（または最小値）が先頭に来るキュー。  
「今ある選択肢の中から最善を取る」グリーディ問題でよく使う。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // デフォルトは最大ヒープ
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    cout << pq.top() << endl; // 4
    pq.pop();
    cout << pq.top() << endl; // 3

    // 最小ヒープにする
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(4);
    cout << min_pq.top() << endl; // 1
}
```

| 操作 | 計算量 |
| --- | --- |
| push | O(log N) |
| top | O(1) |
| pop | O(log N) |

### 典型：K 番目に小さい値を取り出す

```cpp
// N 個の要素から K 番目に小さいものを求める
priority_queue<int> pq; // 最大ヒープをサイズ K で維持
rep(i, n) {
    pq.push(a[i]);
    if ((int)pq.size() > k) pq.pop(); // K+1 番目に大きいものを除去
}
cout << pq.top() << endl; // K 番目に小さい値
```

---

## 3-4. Set（集合）

重複なし・ソート済みの集合。  
「含まれているか？」「最小値は？」を O(log N) で確認できる。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> s;
    s.insert(3);
    s.insert(1);
    s.insert(4);
    s.insert(1); // 重複は無視される

    cout << s.size() << endl;  // 3
    cout << s.count(3) << endl; // 1（含まれる）
    cout << s.count(5) << endl; // 0（含まれない）

    // 最小値・最大値
    cout << *s.begin() << endl;  // 1（最小）
    cout << *s.rbegin() << endl; // 4（最大）

    s.erase(3); // 削除

    // lower_bound で「x 以上の最小値」
    auto it = s.lower_bound(2);
    cout << *it << endl; // 4（2以上の最小値）
}
```

| 操作 | 計算量 |
| --- | --- |
| insert | O(log N) |
| count / find | O(log N) |
| erase | O(log N) |
| begin / rbegin | O(1) |

**重複を許す場合は `multiset<int>` を使う。**

---

## 3-5. Map（連想配列）

キーから値への辞書。  
「この文字列が何回出てきたか」などの頻度カウントに便利。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> cnt;
    cnt["apple"]++;
    cnt["banana"]++;
    cnt["apple"]++;

    cout << cnt["apple"] << endl;  // 2
    cout << cnt.count("grape") << endl; // 0（存在しない）

    // 全要素をループ
    for (auto& [key, val] : cnt) {
        cout << key << ": " << val << endl;
    }
    // apple: 2
    // banana: 1
}
```

**高速版**：順序不要なら `unordered_map` を使うと O(1) 平均になる。  
ただし最悪 O(N) になる場合があるため、ハック対策が必要な場合は要注意。

```cpp
unordered_map<int, int> mp;
mp[key] = value;
```

---

## 3-6. データ構造の使い分けまとめ

| やりたいこと | 使うデータ構造 |
| --- | --- |
| 最大値/最小値を素早く取り出したい | priority_queue |
| 重複なし・存在確認したい | set |
| 重複あり・順序付きで管理 | multiset |
| キーと値を対応付けたい | map |
| 要素の出現回数を数えたい | map または unordered_map |
| LIFO な操作 | stack |
| FIFO な操作（BFS） | queue |

---

## 練習問題

| 問題 | テーマ | 難易度 |
| --- | --- | --- |
| [ABC241B - Sequence Scores](https://atcoder.jp/contests/abc241/tasks/abc241_b) | map / set | ★☆☆ |
| [ABC085B - Kagami Mochi](https://atcoder.jp/contests/abc085/tasks/abc085_b) | set | ★☆☆ |
| [ABC217D - Cutting Woods](https://atcoder.jp/contests/abc217/tasks/abc217_d) | set + lower_bound | ★★★ |
| [ABC212D - Zap](https://atcoder.jp/contests/abc212/tasks/abc212_d) | priority_queue | ★★☆ |
| [ABC141D - Powerful Discount Tickets](https://atcoder.jp/contests/abc141/tasks/abc141_d) | priority_queue | ★★☆ |
