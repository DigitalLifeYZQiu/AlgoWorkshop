//
// Created by Yunzhong Qiu on 2026/8/25.
//
// 洛谷 P1514 [NOIP 2010 提高组] 引水入城
// 题意：N×M 矩形，每格有海拔。第一行可建蓄水厂，水只能流向"相邻且海拔更低"的格子，
//       要求最后一行每座城市都有水。第一问判断是否可行（否则统计不可达城市数），
//       第二问求最少蓄水厂数。
// 思路：
//   第一问：多源 BFS（从第一行出发，正向标记可达）。
//   第二问：关键引理——每个蓄水厂能浇灌的最后一行城市是一段连续区间 [L,R]；
//           按海拔升序求每个格子的区间（等价记忆化搜索的迭代版，避免递归爆栈）；
//           再用贪心做最小区间覆盖 [1,M]。
//

#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<utility>

using namespace std;

const int INF = 1e9;

int N, M;
int h[505][505];               // 海拔
int L[505][505], R[505][505];  // (i,j) 能到达的最后一行城市的最左/最右列
bool reach[505][505];          // 第一问：从第一行能否到达
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 用 struct 代替 tuple，避免依赖 <tuple> 头文件的间接包含
struct Cell { int h, x, y; };

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=M; j++)
        {
            cin>>h[i][j];
        }
    }

    // ---------- 第一问：多源 BFS，从第一行正向标记可达 ----------
    queue<pair<int, int>> q;
    for (int j=1; j<=M; j++)
    {
        reach[1][j] = true;
        q.push({1, j});
    }
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int d=0; d<4; d++)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            if (reach[nx][ny] || h[nx][ny] >= h[x][y]) continue;  // 严格低于才能流
            reach[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    int un = 0;
    for (int j=1; j<=M; j++)
    {
        if (!reach[N][j]) un++;
    }
    if (un > 0)                          // 有城市到不了
    {
        cout<<0<<endl<<un<<endl;
        return 0;
    }

    // ---------- 第二问：按海拔升序求每个格子的覆盖区间 ----------
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=M; j++)
        {
            L[i][j] = INF, R[i][j] = 0;
        }
    }

    vector<Cell> cells;
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=M; j++)
        {
            cells.push_back({h[i][j], i, j});
        }
    }
    // 按高度升序排序（用 lambda 比较器）
    sort(cells.begin(), cells.end(),
         [](const Cell& a, const Cell& b) { return a.h < b.h; });

    for (auto &c : cells)
    {
        int x = c.x, y = c.y;
        if (x==N)                           // 最后一行城市本身
        {
            L[x][y] = min(L[x][y], y);
            R[x][y] = max(R[x][y], y);
        }
        for (int d=0; d<4; d++)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx<1 || nx>N || ny<1 || ny>M) continue;
            if (h[nx][ny] >= h[x][y]) continue;   // 更低邻居，升序下已处理过
            L[x][y] = min(L[x][y], L[nx][ny]);    // 合并区间
            R[x][y] = max(R[x][y], R[nx][ny]);
        }
    }

    // 收集第一行每个格子的区间
    vector<pair<int, int>> seg;
    for (int j=1; j<=M; j++)
    {
        if (L[1][j] <= R[1][j])             // 能到达至少一个最后一行城市
            seg.push_back({L[1][j], R[1][j]});
    }
    sort(seg.begin(), seg.end());           // 按左端点排序

    // ---------- 贪心：用最少的区间覆盖 [1, M] ----------
    int ans = 0, now = 1, idx = 0, sz = seg.size();
    while (now <= M)
    {
        int far = now - 1;
        while (idx < sz && seg[idx].first <= now)   // 左端点 <= 当前已覆盖位置
        {
            far = max(far, seg[idx].second);        // 选右端点最远的
            idx++;
        }
        ans++;
        now = far + 1;
    }
    cout<<1<<endl<<ans<<endl;
    return 0;
}
