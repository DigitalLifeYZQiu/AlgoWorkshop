//
// Created by Yunzhong Qiu on 2026/8/24.
//
// 洛谷 P3956 [NOIP2017 普及组] 棋盘 —— SPFA（BFS 风格）写法
// 题意：m×m 棋盘，格子分红(0)/黄(1)/无色(-1)。从 (1,1) 走到 (m,m) 求最少金币。
//       同色移动花 0，异色花 1；可花 2 用魔法让相邻无色格临时变色并走过去，
//       但魔法不能连续使用。
// 思路：边权是 0/1/2 不均匀，普通 BFS（按步数）会错，这里用 SPFA：
//       队列 + 反复松弛，节点只要被更新出更小花费就重新入队。
// 注意：与 Dijkstra 版相比，SPFA 用普通 queue，状态可多次入队，最坏 O(VE)，
//       但本题状态空间小（约 4 万个），完全可行。
//

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int m, n;
int grid[105][105];            // grid[x][y]：-1 无色，0 红，1 黄
int dist[105][105][2][2];      // dist[x][y][color][used]：到某状态的最小花费
bool inq[105][105][2][2];      // inq[x][y][color][used]：该状态是否已在队列中
int dx[4] = {-1, 1, 0, 0};     // 上下左右四个方向
int dy[4] = {0, 0, -1, 1};

struct State
{
    int x, y, color, used;     // 位置 + 当前颜色 + 是否刚用过魔法
};

void spfa()
{
    memset(dist, 0x3f, sizeof(dist));   // 初始化为无穷大
    queue<State> q;

    // 起点 (1,1) 一定有颜色，是"真实有色"格子，used=0
    dist[1][1][grid[1][1]][0] = 0;
    q.push({1, 1, grid[1][1], 0});
    inq[1][1][grid[1][1]][0] = true;

    while (!q.empty())
    {
        State s = q.front();
        q.pop();
        inq[s.x][s.y][s.color][s.used] = false;   // 出队后清除标记（之后可再次入队）
        int cur = dist[s.x][s.y][s.color][s.used]; // 用"当前最新"的花费去松弛

        for (int d = 0; d < 4; d++)
        {
            int nx = s.x + dx[d], ny = s.y + dy[d];
            if (nx < 1 || nx > m || ny < 1 || ny > m) continue;   // 越界

            if (grid[nx][ny] != -1)
            {
                // ① 邻居是真实有色格子：同色花 0，异色花 1
                int c2 = grid[nx][ny];
                int nc = cur + (c2 == s.color ? 0 : 1);
                if (nc < dist[nx][ny][c2][0])        // 找到更小花费 → 松弛
                {
                    dist[nx][ny][c2][0] = nc;
                    if (!inq[nx][ny][c2][0])         // 不在队列才入队
                    {
                        q.push({nx, ny, c2, 0});
                        inq[nx][ny][c2][0] = true;
                    }
                }
            }
            else
            {
                // ② 邻居是无色格子：必须当前是真实格(used==0)才能用魔法
                if (s.used == 1) continue;           // 不能连续用魔法
                int nc = cur + 2;                    // 魔法固定花 2
                if (nc < dist[nx][ny][s.color][1])
                {
                    dist[nx][ny][s.color][1] = nc;   // 魔法格继承当前颜色
                    if (!inq[nx][ny][s.color][1])
                    {
                        q.push({nx, ny, s.color, 1});
                        inq[nx][ny][s.color][1] = true;
                    }
                }
            }
        }
    }
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

    spfa();

    int ans = INF;
    for (int c = 0; c < 2; c++)
        for (int u = 0; u < 2; u++)
            ans = min(ans, dist[m][m][c][u]);   // 终点可能是真实格或魔法格
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}
