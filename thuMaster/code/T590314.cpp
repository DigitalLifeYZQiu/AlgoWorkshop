//
// Created by Yunzhong Qiu on 2026/8/26.
//
// 洛谷 T590314 任务分配（O(n log n) 满分版）
// 题意：n 个点的有根树，n 个任务（耗时 t_i 已升序）一一分配到节点，
//       节点 i 的子树内所有任务耗时 <= w_i。可把一个节点的 w 增加 k，求最小 k。
//
// 核心转化与结论（均已随机对拍验证）：
//   1. 节点容量 cap[v] = min(根到 v 路径上的 w)；任务 t 能放 v <=> t <= cap[v]。
//   2. 判定：对每个阈值 v，容量>=v 的个数 >= 任务>=v 的个数（等价于排序贪心）。
//   3. 答案 = V0 - max(有效节点的 w)：
//        V0 = 最大的"有缺口阈值"；有效节点 x = 把 w_x 抬到 V0 后能合法。
//   4. "有效"可进一步判定：x 的 w_x < V_min（最小缺口阈值），且
//       x 所"瓶颈"的节点们的"可达值"（第二小 w）排序后能支配缺口分布。
//
// 实现：
//   - 一遍树形递推求 cap、第二小值 mn2、最小值出现次数、瓶颈节点 b；
//   - 按瓶颈分组得到每个节点的"可达值"多重集；
//   - 对每组排序后与"缺口需求 req"做支配（majorization）检查。
// 复杂度：O(n log n)。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
int f[100005], w[100005], t[100005];   // 父亲、限制、任务耗时

int cap[100005];      // cap[v] = 根到 v 路径上 w 的最小值
int mn2[100005];      // 路径上"第二小"的 w（若最小值唯一，即抬升后可达值）
int mn1cnt[100005];   // 路径上最小值出现的次数（>1 表示有并列，无法靠单点抬升）
int b[100005];        // 瓶颈节点（路径上最浅的最小值节点）

vector<int> B[100005];   // B[x] = 瓶颈为 x 且"最小值唯一"的节点的可达值集合

int A[100005];   // A[v] = 耗时 >= v 的任务数（后缀计数）
int cnt[100005]; // 计数桶
int d[100005];   // d[v] = A[v] - B[v]（容量>=v 的个数），即阈值 v 处的缺口

int solve()
{
    // ---------- 1. 树形递推：cap / mn2 / mn1cnt / b（f_i < i，按序号即可） ----------
    cap[1] = w[1]; mn2[1] = n + 1; mn1cnt[1] = 1; b[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        int p = f[i];
        if (w[i] < cap[p])              // 出现更小值：成为新的最小值
        {
            cap[i] = w[i];
            mn2[i] = cap[p];            // 旧最小值变为第二小
            mn1cnt[i] = 1;
            b[i] = i;
        }
        else if (w[i] == cap[p])        // 与最小值相等：出现并列
        {
            cap[i] = cap[p];
            mn2[i] = mn2[p];
            mn1cnt[i] = mn1cnt[p] + 1;
            b[i] = b[p];
        }
        else                            // 大于最小值：可能更新第二小
        {
            cap[i] = cap[p];
            mn2[i] = min(mn2[p], w[i]);
            mn1cnt[i] = mn1cnt[p];
            b[i] = b[p];
        }
    }

    // 只有"最小值唯一"的节点可被抬升，按瓶颈分组
    for (int i = 1; i <= n; i++)
        if (mn1cnt[i] == 1) B[b[i]].push_back(mn2[i]);

    // ---------- 2. A[v]（任务后缀计数） ----------
    for (int i = 1; i <= n; i++) A[t[i]]++;
    for (int v = n - 1; v >= 1; v--) A[v] += A[v + 1];

    // ---------- 3. d[v] = 缺口；求 V0 / V_min / M ----------
    for (int i = 1; i <= n; i++) cnt[cap[i]]++;
    int Bsum = 0, V0 = 0, V_min = n + 1, M = 0;
    for (int v = n; v >= 1; v--)
    {
        Bsum += cnt[v];
        d[v] = A[v] - Bsum;
        if (d[v] > 0) { V0 = max(V0, v); V_min = min(V_min, v); M = max(M, d[v]); }
    }
    if (V0 == 0) return 0;   // 原本就合法

    // ---------- 4. req[j] = max{v : d[v] >= j}（j=1..M，非递增） ----------
    vector<int> req(M + 1, 0);
    int cur = n;
    for (int j = 1; j <= M; j++)
    {
        while (cur >= 1 && d[cur] < j) cur--;
        req[j] = cur;
    }

    // ---------- 5. 枚举节点，检查其可达值是否支配缺口 ----------
    int bestW = -1;
    for (int x = 1; x <= n; x++)
    {
        if (w[x] >= V_min) continue;        // 抬升前必须低于最小缺口阈值
        vector<int>& rv = B[x];
        if ((int)rv.size() < M) continue;   // 可达值数量不足
        sort(rv.rbegin(), rv.rend());       // 降序
        bool ok = true;
        for (int j = 1; j <= M; j++)
            if (rv[j - 1] < req[j]) { ok = false; break; }   // 第 j 大可达值 >= 第 j 大需求
        if (ok) bestW = max(bestW, w[x]);
    }
    return bestW == -1 ? -1 : V0 - bestW;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> f[i];
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    cout << solve() << '\n';
    return 0;
}
