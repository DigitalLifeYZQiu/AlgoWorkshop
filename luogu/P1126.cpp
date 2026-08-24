//
// Created by Yunzhong Qiu on 2026/8/24.
//
// 洛谷 P1126 机器人搬重物
// 题意：N×M 网格（0 无障碍 1 障碍），机器人是直径 1.6 的圆，中心在格点上。
//       指令：前进 1/2/3 步、左转、右转（各 1 秒）。求从起点到终点的最短时间。
// 思路：机器人直径 1.6 > 1，中心在格点时身体压到周围 2×2 格子，
//       所以"格点能站"等价于周围 2×2 格子都无障碍；BFS 状态带朝向。
//

#include<iostream>
#include<queue>
#include<cstring>          // memset 在这里（而不是 <string>）
using namespace std;

int N, M;
int grid[55][55];           // 0-indexed，0 无障碍 1 障碍
int dist[55][55][4];        // dist[i][j][dir]：到 (i,j) 且朝向 dir 的最短时间，-1 未访问
int dx[4] = {-1, 0, 1, 0};  // 朝向 0=N(上) 1=E(右) 2=S(下) 3=W(左) 的行偏移
int dy[4] = {0, 1, 0, -1};  // 对应的列偏移

struct Node {int r, c, d;};  // 格点行、格点列、朝向

// 格点 (i,j) 能否站：以它为中心（左上）的 2×2 格子都无障碍
bool ok(int i, int j)
{
    for (int r=i-1; r<=i; r++)
    {
        for (int c=j-1; c<=j; c++)
        {
            if (r>=0 && r<N && c>=0 && c<M && grid[r][c] == 1)
            {
                return false;   // 界内格子有障碍 → 不能站
            }
        }
    }
    return true;
}

int bfs(int sr, int sc, int sd, int tr, int tc)
{
    memset(dist, -1, sizeof(dist));
    queue<Node> q;
    q.push({sr, sc, sd});
    dist[sr][sc][sd] = 0;

    while (!q.empty())
    {
        Node s = q.front(); q.pop();
        int r = s.r, c = s.c, d = s.d;
        if (r==tr && c==tc) return dist[r][c][d];   // 到达终点（朝向任意）

        // 转向：左转 (d+3)%4，右转 (d+1)%4
        int dl = (d+3) % 4, dr2 = (d+1)%4;
        if (dist[r][c][dl] == -1)
        {
            dist[r][c][dl] = dist[r][c][d] + 1;
            q.push({r,c,dl});
        }
        if (dist[r][c][dr2] == -1)
        {
            dist[r][c][dr2] = dist[r][c][d] + 1;
            q.push({r, c, dr2});
        }

        // 前进 1/2/3 步：逐步检查，途中遇到障碍或越界就 break
        for (int k=1; k<=3; k++)
        {
            int nr = r + dx[d] * k, nc = c + dy[d] * k;
            if (nr < 0 || nr > N || nc < 0 || nc > M) break;   // 越界（行范围 0..N）
            if (!ok(nr, nc)) break;                            // 途中遇障碍，无法再往前
            if (dist[nr][nc][d] == -1)
            {
                dist[nr][nc][d] = dist[r][c][d] + 1;
                q.push({nr, nc, d});
            }
        }
    }
    return -1;   // 无法到达
}

int main()
{
    cin>>N>>M;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M; j++)
        {
            cin>>grid[i][j];
        }
    }
    int sr, sc, tr, tc;
    char ch;
    cin>>sr>>sc>>tr>>tc>>ch;
    int sd;
    if (ch == 'N') sd = 0;      // N = 上
    else if (ch == 'E') sd = 1; // E = 右
    else if (ch == 'S') sd = 2; // S = 下
    else sd = 3;                // W = 左

    cout<<bfs(sr, sc, sd, tr, tc)<<endl;
    return 0;
}
