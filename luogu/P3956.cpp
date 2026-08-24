//
// Created by Yunzhong Qiu on 2026/8/23.
//
// 洛谷 P3956 [NOIP2017 普及组] 棋盘
// 题意：m×m 棋盘，格子分红(0)/黄(1)/无色(-1)。从 (1,1) 走到 (m,m) 求最少金币。
//       同色移动花 0，异色花 1；可花 2 用魔法让相邻无色格临时变色并走过去，
//       但魔法不能连续使用。
// 思路：状态需带"是否刚用过魔法"(used)，用 Dijkstra 求带权最短路（边权 0/1/2）。
//

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int m, n;
int grid[105][105];            // grid[x][y]：-1 无色，0 红，1 黄
int dist[105][105][2][2];      // dist[x][y][color][used]：到某状态的最小花费
int dx[4] = {-1, 1, 0, 0};     // 上下左右四个方向
int dy[4] = {0, 0, -1, 1};

// Dijkstra 的状态：位置 + 当前颜色 + 是否刚用过魔法 + 已花费金币
struct State
{
    int x, y, color, used, cost;
    bool operator<(const State& o) const { return cost > o.cost; }  // 重载 < 反转成小根堆
};

int dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));   // 初始化为无穷大
    priority_queue<State> pq;

    // 起点 (1,1) 一定有颜色，是"真实有色"格子，used=0（可用魔法）
    dist[1][1][grid[1][1]][0] = 0;
    pq.push({1, 1, grid[1][1], 0, 0});

    while (!pq.empty())
    {
        State s = pq.top();
        pq.pop();
        // 该状态已不是最优（被更小花费更新过），跳过这个过期节点
        if (s.cost > dist[s.x][s.y][s.color][s.used]) continue;

        for (int d = 0; d < 4; d++)
        {
            int nx = s.x + dx[d], ny = s.y + dy[d];
            if (nx < 1 || nx > m || ny < 1 || ny > m) continue;   // 越界

            if (grid[nx][ny] != -1)
            {
                // ① 邻居是真实有色格子：同色花 0，异色花 1
                int c2 = grid[nx][ny];
                int nc = s.cost + (c2 == s.color ? 0 : 1);
                if (nc < dist[nx][ny][c2][0])
                {
                    dist[nx][ny][c2][0] = nc;
                    pq.push({nx, ny, c2, 0, nc});   // 到真实格，魔法恢复可用(used=0)
                }
            }
            else
            {
                // ② 邻居是无色格子：必须当前是真实格(used==0)才能用魔法
                if (s.used == 1) continue;           // 不能连续用魔法
                int nc = s.cost + 2;                 // 魔法固定花 2
                // 魔法格颜色指定为当前颜色（这步不多花异色的 1，且不影响后续最优）
                if (nc < dist[nx][ny][s.color][1])
                {
                    dist[nx][ny][s.color][1] = nc;
                    pq.push({nx, ny, s.color, 1, nc});  // 到魔法格，used=1 不可再用魔法
                }
            }
        }
    }

    // 终点 (m,m) 可能是真实格或魔法格，取所有状态的最小值
    int ans = INF;
    for (int c = 0; c < 2; c++)
        for (int u = 0; u < 2; u++)
            ans = min(ans, dist[m][m][c][u]);
    return ans == INF ? -1 : ans;
}

int main()
{
    cin >> m >> n;
    memset(grid, -1, sizeof(grid));   // 初始全部无色
    for (int i = 0; i < n; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        grid[x][y] = c;               // 标记有颜色的格子
    }
    cout << dijkstra() << endl;
    return 0;
}
