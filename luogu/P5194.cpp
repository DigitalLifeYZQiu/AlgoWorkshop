//
// Created by Yunzhong Qiu on 2026/8/22.
//
// 洛谷 P5194 [USACO05DEC] Scales S 天平
// 题意：N 个砝码（非递减，且从第 3 个起每个 >= 前两个质量之和），
//       选出若干砝码使总质量 <= C 且最大，输出这个最大总质量。
// 思路：质量 > C 的砝码永远用不上，直接丢弃；由斐波那契式增长可知
//       有效砝码最多约 46 个；再 DFS + 前缀和剪枝枚举子集。
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int n;
long long C, ans;
vector<long long> w;     // 过滤后（质量 <= C）的砝码，保持升序
vector<long long> pre;   // pre[i] = w[0..i] 的前缀和

// 考虑下标 idx 的砝码（从大到小），当前已选总质量为 cur
void dfs(int idx, long long cur)
{
    ans = max(ans, cur);                 // 每个状态都可能是答案
    if (idx < 0) return;                 // 所有砝码都已考虑完

    // 前缀和剪枝：剩余所有砝码全选也超不过当前最优，直接返回
    if (cur + pre[idx] <= ans) return;

    // 优先"选"当前砝码（更快得到接近 C 的答案，增强剪枝效果）
    if (cur + w[idx] <= C)
        dfs(idx - 1, cur + w[idx]);
    // "不选"当前砝码
    dfs(idx - 1, cur);
}

int main()
{
    cin >> n >> C;

    // ---------- 读入并过滤：质量 > C 的砝码永远用不上 ----------
    w.reserve(n);                        // 预留容量，避免反复扩容
    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        if (x <= C) w.push_back(x);      // 只保留 <= C 的砝码
    }

    // ---------- 计算前缀和 ----------
    int m = w.size();
    pre.resize(m);
    partial_sum(w.begin(), w.end(), pre.begin());  // pre[i] = w[0] + ... + w[i]

    // ---------- DFS：从最大的砝码开始考虑 ----------
    dfs(m - 1, 0);

    cout << ans << endl;
    return 0;
}
