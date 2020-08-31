---
title: Leetcode Weekly Contest 204
date: 2020-09-01 03:56:33
categories:
  - LeetCode
  - LeetCode Contest
tags:
mathjax: true
---
听小姐姐的话把语言换成了C++，开始复健之路。

<!-- more -->

[比赛地址](https://leetcode.com/contest/weekly-contest-204)

## 1566. Detect Pattern of Length M Repeated K or More Times

简单题，询问存不存在长度为$m$的子串重复了$k$次，循环即可。

```cpp
class Solution
{
public:
    bool containsPattern(vector<int> &arr, int m, int k){
        for (int i = 0; i < arr.size() - m * (k - 1); i++){
            bool same_ptn = true;
            for (int j = 0; j < m; j++){
                for (int jk = 0; jk < k; jk++){
                    if (arr[i + j + m * jk] != arr[i + j]){
                        same_ptn = false;
                        break;
                    }
                }
                if (!same_ptn) break;
            }
            if (same_ptn) return true;
        }
        return false;
    }
};
```

## 1567. Maximum Length of Subarray With Positive Product

询问最长的乘积为正数的子串有多长。

我们要考虑一下几点：

- 如果一个数是0，那么它不可能被包含在这个子串中，否则乘积会变成0。
- 如果一个数是正数，那么在它之前的乘积为正数的子串乘上它依然为正数，乘积为负数的子串乘上它依然为负数。
- 如果一个数是负数，那么在它之前的乘积为正数的子串乘上它会变成负数，乘积为负数的子串乘上它会变为正数。

所以，我们的转移过程就很简单了：

- 使用`dp[0][i]`来表示到当前位置`i`最长的负乘积子串长度，使用`dp[1][i]`表示到当前位置`i`最长的正乘积子串长度，如果没有此种子串则长度为-1。
- 分类讨论：
  1. 如果`nums[i]==0`，那么`dp[0][i]=dp[1][i]=-1`；
  2. 如果`nums[i]>0`，那么如果前面的子串长度不为-1（即存在）则可以长度+1，如果是-1（不存在）则将`dp[1][i]`重置为1；
  3. 如果`nums[i]<0`，那么如果前面的子串长度不为-1（即存在）则可以长度+1，如果是-1（不存在）则将`dp[0][i]`重置为1；
- 需要注意的是，`nums[i]<0`时由于乘上负数需要变换符号，转移方程和`nums[i]>0`相反。

基本属于DP入门题了233333。

```cpp
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int dp[2][100005];
        dp[0][0] = nums[0]<0?1:-1;
        dp[1][0] = nums[0]>0?1:-1;
        for (int i=1;i<nums.size();i++){
            if(nums[i]==0){
                dp[0][i] = -1;
                dp[1][i] = -1;
            }else if(nums[i] > 0){
                dp[0][i] = dp[0][i-1]>=0?dp[0][i-1] + 1:-1;
                dp[1][i] = dp[1][i-1]>=0?dp[1][i-1] + 1:1;
            }else{
                dp[0][i] = dp[1][i-1]>=0?dp[1][i-1] + 1:1;
                dp[1][i] = dp[0][i-1]>=0?dp[0][i-1] + 1:-1;
            }
        }
        int ans = 0;
        for (int i=0;i<nums.size();i++){
            ans = max(ans, dp[1][i]);
        }
        return ans;
    }
};
```

## 1568. Minimum Number of Days to Disconnect Island

询问在一个2D grid中删掉最少多少岛屿可以使其不连通。

很tricky的一道题。考虑最左上角的岛屿，其最多拥有两个邻居（否则它的左上应当存在别的岛屿），所以最后答案不会超过2。

剩下的只需要暴力判断能不能只删除一个让其不连通即可。

```cpp
typedef pair<int,int> P;
class Solution {
public:
    bool vis[30][30];
    P dir[4] = {
        P(0,1), P(0, -1), P(-1,0), P(1,0)
    };
    void BFS(vector<vector<int>>& grid, int x, int y){
        int n = grid.size();
        int m = grid[0].size();
        queue<P> Q;
        Q.push(P(x, y));
        while(!Q.empty()){
            P p = Q.front();
            Q.pop();
            int i = p.first;
            int j = p.second;
            if (vis[i][j]) continue;
            vis[i][j] = 1;
            for (int k = 0; k < 4; k++){
                P d = dir[k];
                int ii = i + d.first, jj = j + d.second;
                if (ii>=0 && ii<n && jj>=0 && jj<m && grid[ii][jj] && !vis[ii][jj])
                    Q.push(P(ii,jj));
            }
        }
    }
    bool checkDisConn(vector<vector<int>>& grid){
        int n = grid.size();
        int m = grid[0].size();
        memset(vis, 0, sizeof(vis));
        bool searched = false;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j]){
                    BFS(grid, i, j);
                    searched = true;
                    break;
                }
            }
            if (searched) break;
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j] && !vis[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
    int minDays(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if (checkDisConn(grid)) return 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j]){
                    grid[i][j] = 0;
                    if (checkDisConn(grid)) return 1;
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
};
```

如果不是2D的图，这个问题实际上是求无向图的最小点割集，可以通过以下方法求解：

- 将点$v$拆分为$v_1, v_2$，连接$w(v_1, v_2)=1$。
- 边$(u,v)$变为$(u_2,v_1)$与$(v_2,u_1)$，并$w(u_2,v_1)=w(v_2,u_1)=\infty$。
- 源点$s$，$w(s,v_1)=\infty, \forall v $ 。
- 汇点$t$，$w(v_2,t)=\infty, \forall v $ 。
- 求最小割/最大流。

这就过于复杂了，不像是LeetCode的题。

## 1569. Number of Ways to Reorder Array to Get Same BST

询问有多少种元素的排列可以形成相同的BST。

简单的排列组合题。

![demo.png](https://i.loli.net/2020/09/01/CENrliomK7FxJWn.png)

以这个例子为例，我们发现：

- root不变（似乎是废话）
- 左子树的元素的相对顺序不变
- 右子树的元素的相对顺序不变

我们小学二年级就学过，分组相对顺序不变的排列个数计算只需要总排列个数除以每组的排列个数即可。

因此，我们可以分治递归来解决这个问题，需要注意的是：

- 除以左右子树的排列数后要乘上左右子树的递归解。
- 同余类下的除法需要计算逆元。
- 阶乘可以预处理。
- 开long long避免乘法溢出int32。
- 最后结果记得-1，因为询问的是**还有**多少种可能的方案。

```cpp
#define LL long long
#define pb push_back
class Solution {
public:
    LL MOD = 1e9+7;
    LL fact[1005];
    void initFact(){
        LL f = 1;
        fact[0] = f;
        for (LL i=1;i<=1000;i++){
            fact[i] = (fact[i-1] * i) % MOD;
        }
    }
    void exgcd(LL a,LL b,LL& d,LL& x,LL& y){
        if(!b) { d = a; x = 1; y = 0; }
        else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
    }
    LL inv(LL a, LL p){
        LL d,x,y;
        exgcd(a,p,d,x,y);
        return d == 1 ? (x+p)%p : -1;
    }
    LL handleSubTree(vector<int> & nums){
        if (nums.size()<=1) return 1;
        vector<int> leftT, rightT;
        for (int i=1;i<nums.size();i++){
            if (nums[i]<nums[0]) leftT.pb(nums[i]);
            else rightT.pb(nums[i]);
        }
        LL invL = leftT.size()>1?inv(fact[leftT.size()], MOD):1;
        LL invR = rightT.size()>1?inv(fact[rightT.size()], MOD):1;
        LL ans = ((fact[nums.size()-1] * invL) % MOD * invR) % MOD;
        ans = (ans * handleSubTree(leftT)) % MOD;
        ans = (ans * handleSubTree(rightT)) % MOD;
        return ans;
    }
    int numOfWays(vector<int>& nums) {
        initFact();
        return (int)((handleSubTree(nums)+MOD-1)%MOD);
    }
};
```

