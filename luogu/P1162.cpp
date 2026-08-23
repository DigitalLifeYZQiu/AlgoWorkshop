//
// Created by Yunzhong Qiu on 2026/8/23.
//
// 洛谷 P1162 填涂颜色
// 题意：n×n 方阵中，数字 1 构成一个闭合圈，把圈内的 0 全部改成 2，圈外的 0 保持不动。
// 思路：逆向思维——圈外的 0 一定与边界连通，圈内的 0 被 1 围住到不了边界。
//       给矩阵外加一圈虚拟 0 边界，从 (0,0) 做 BFS 洪水填充，能到达的 0 是圈外，
//       到不了的 0 就是圈内，改成 2。
//

#include<iostream>
#include<queue>
using namespace std;

int n;
int g[35][35];          // 加一圈 0 边界后的矩阵（n <= 30，下标 0..n+1）
bool vis[35][35];       // vis[i][j]：从圈外能否到达该格子
int dx[4] = {-1,1,0,0}; // 上下左右四个方向的 x 偏移
int dy[4] = {0,0,-1,1}; // 上下左右四个方向的 y 偏移

// 从 (sx, sy) 开始 BFS，把连通的"0"全部标记为圈外可达
void bfs(int sx, int sy)
{
    queue<pair<int, int>> q;
    q.push({sx, sy});          // 起点入队
    vis[sx][sy] = true;        // 标记起点已访问
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        int cx = cur.first, cy = cur.second;   // 当前格子坐标
        for (int d=0; d<4; d++)                // 尝试四个方向
        {
            int nx = cx + dx[d], ny = cy + dy[d];
            if (nx < 0 || nx > n+1 || ny < 0 || ny > n+1) continue; // 越界（含虚拟边界）
            if (vis[nx][ny] || g[nx][ny] == 1) continue;            // 已访问或是墙(1)
            vis[nx][ny] = true;    // 标记可达
            q.push({nx, ny});      // 入队，继续扩散
        }
    }
}

int main()
{
    cin>>n;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            cin>>g[i][j];   // 读入原矩阵，虚拟边界一圈默认是 0
        }
    }

    bfs(0,0);               // 从虚拟边界的 (0,0) 开始"灌水"

    for (int i=1;i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            if (g[i][j] == 0 && !vis[i][j])   // 是 0 但圈外到不了 → 在闭合圈内
            {
                g[i][j] = 2;                  // 填成 2
            }
            cout<<g[i][j]<<(j==n ? '\n' : ' '); // 输出，行末换行，中间空格
        }
    }
    return 0;
}
