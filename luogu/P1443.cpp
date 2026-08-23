//
// Created by Yunzhong Qiu on 2026/8/23.
//
// 洛谷 P1443 马的遍历
// 题意：n×m 棋盘，马从 (x,y) 出发，按"日"字走 8 个方向，
//       求到每个格子的最少步数，不可达输出 -1。
// 思路：无权图最短路 → BFS 按层扩散，第一次到达某格就是最短路。
//

#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;

int n, m;
int dist[405][405];          // dist[i][j]：到 (i,j) 的最少步数，-1 表示未访问/不可达
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  // 马的 8 个"日"字方向的 x 偏移
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};  // 马的 8 个方向的 y 偏移

// 从起点 (sx, sy) 开始 BFS，求到每个格子的最短路
void bfs(int sx, int sy)
{
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;                    // 起点 0 步
    while (!q.empty())
    {
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        for (int d=0; d<8; d++)          // 枚举 8 个方向
        {
            int nx = cx + dx[d], ny = cy + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny >m) continue;  // 越界（坐标 1-based）
            if (dist[nx][ny] != -1) continue;                   // 已访问过，跳过
            dist[nx][ny] = dist[cx][cy] + 1;                    // 步数 +1
            q.push({nx, ny});
        }
    }
}

int main()
{
    int sx, sy;
    cin>>n>>m>>sx>>sy;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            dist[i][j] = -1;             // 初始化为"不可达"
        }
    }
    bfs(sx, sy);

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            printf("%-5d", dist[i][j]);  // 每个数占 5 字符宽度、左对齐
        }
        printf("\n");
    }
    return 0;
}
