---
title: LeetCode Weekly Contest 152
date: 2019-9-2 21:47:09
categories:
  - LeetCode
  - LeetCode Contest
tags:
mathjax: true
---
一场艰难的复健之旅。
<!-- more -->

## 1175. Prime Arrangements

问1~n的排列中，质数位于质数位置的情况有多少种。

质数全排列，合数全排列即可，答案为 $φ(n)!*(n-φ(n))!$ 。

```python
class Solution:
    def numPrimeArrangements(self, n: int) -> int:
        pl = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]
        s = sum([i <= n for i in pl])
        ans = 1
        for i in range(1, s+1):
            ans *= i
            ans %= (10**9+7)
        for i in range(1, (n-s)+1):
            ans *= i
            ans %= (10**9+7)
        return ans
```

## 1176. Diet Plan Performance

长度为 $k$ 的连续子区间的和< lower丢1分，> upper得一分，问最后得分。

简单求和。

```python
class Solution:
    def dietPlanPerformance(self, calories, k: int, lower: int, upper: int) -> int:
        cnt = 0
        s = 0
        ans = 0
        for idx, cal in enumerate(calories):
            s += cal
            if idx >= k-1:
                if s > upper:
                    ans += 1
                if s < lower:
                    ans -= 1
            if idx-k+1 >= 0:
                s -= calories[idx-k+1]
        return ans
```

## 1177. Can Make Palindrome from Substring

问区间内可以重排列的情况下最多改变 $k$ 个字母能否使字符串回文，离线查询。

一开始读错了题，不知道还可以重排列，对着一个错误样例思考了半天人生，直接导致最后一题没有时间完成，太菜了.jpg

既然可以重排列，直接统计有多少个字母是奇数个即可（因为不需要全替换所以需要除以2）。

离线查询可以针对26个字母分别维护前缀和。

```python
class Solution:
    def canMakePaliQueries(self, s: str, queries: List[List[int]]) -> List[bool]:
        sto = [[0] * 26 for i in range(len(s)+1)]
        for idx, ch in enumerate(s, 1):
            for i in range(26):
                sto[idx][i] = 1 if ((ord(ch)-ord('a'))==i) else 0
                sto[idx][i] += sto[idx-1][i]
        ans = []
        for que in queries:
            l = que[0]+1
            r = que[1]+1
            k = que[2]
            tmp = [0] * 27
            mi = 0
            for i in range(26):
                sum_i = sto[r][i]-sto[l-1][i]
                if (sum_i%2) == 1:
                    mi += 1
            ans.append((mi//2) <= k or l>=r)
        return ans
```

## 1178. Number of Valid Words for Each Puzzle

给`10^5`个words，`10^4`个puzzles，每个puzzle长度为7，符合以下两种条件的word可以match puzzle：

1. puzzle的首字母在word中
2. word的全部字母都在puzzle中

明显位运算，由于word的字母需要全在puzzle中，只记录word对应的bitmask出现次数即可。然后枚举puzzle的所有状态，针对存在puzzle首字母的情况求和。由于puzzle长度为7，2^7才128，所以计算数量级在`2^7*10^4=1*10^5`左右。

神奇的是，python的数组会T，改成Counter就过了（辣鸡python）。

```python
def word2num(word):
    res = 0
    for ch in word:
        res |= (1<<(ord(ch)-ord('a')))
    return res

class Solution:
    def findNumOfValidWords(self, words, puzzles):
        # ch_dict = [0] * (1<<26)  # TLE
        ch_dict = collections.Counter()
        for word in words:
            res = 0
            fs = frozenset(word)
            if len(fs) <= 7:
                for ch in word:
                    res |= (1<<(ord(ch)-ord('a')))
                ch_dict[res] += 1
        ans = []
        for puz in puzzles:
            puz_num = 0
            for ch in puz:
                puz_num |= (1<<(ord(ch)-ord('a')))
            res = 0
            bit = puz_num
            while True:
                if not bit: break
                if (bit >> (ord(puz[0])-ord('a')) & 1 == 1):
                    res += ch_dict[bit]
                bit = (bit - 1) & puz_num
            ans.append(res)
        return ans
```

小Tip：枚举puzzle状态是位运算枚举puzzle的二进制1，算法如下：

```python
bit = mask
while True:
    if not bit: break
    bit = (bit - 1) & mask
```

以`100010100`为例，这段代码运行后的bit情况分别为：

```
100010100
100010000
100000100
100000000
000010100
000010000
000000100
000000000
```

可见是在枚举1的位置。