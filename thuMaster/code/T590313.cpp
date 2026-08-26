//
// Created by Yunzhong Qiu on 2026/8/26.
//
// 洛谷 T590313 Bloxorz
// 题意：n×m 网格，'#'空地、'.'地面、'E'玻璃、'X'初始、'O'目标。
//       一个 1×1×2 的长方体方块，可竖放(1格地面)或平放(相邻2格，非'#')。
//       每次沿某方向滚动 90°，求把方块"竖放"到 O 上的最少操作数。
// 思路：方块有 3 种姿态，用状态 (x, y, lie) 做 BFS 求最少步数：
//       lie=0 竖放；lie=1 横躺(左格为 x,y)；lie=2 竖躺(上格为 x,y)。
//

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
char g[505][505];              // 棋盘
int dist[3][505][505];         // dist[lie][x][y]：到某状态的最少步数，-1 未访问

// 方向：0=上 1=下 2=左 3=右
// nxt[lie][dir] = {dx, dy, 新lie}：滚动后的状态偏移
int nxt[3][4][3] = {
    {{-2, 0, 2}, {1, 0, 2}, {0, -2, 1}, {0, 1, 1}},  // lie=0 站立
    {{-1, 0, 1}, {1, 0, 1}, {0, -1, 0}, {0, 2, 0}},  // lie=1 横躺
    {{-1, 0, 0}, {2, 0, 0}, {0, -1, 2}, {0, 1, 2}},  // lie=2 竖躺
};

struct State { int x, y, lie; };   // 位置 + 姿态

// 判断状态 (x, y, lie) 是否合法（方块能放得住）
bool valid(int x, int y, int lie) {
    if (x < 0 || x >= n || y < 0 || y >= m) return false;   // 越界
    if (lie == 0)
        return g[x][y] != '#' && g[x][y] != 'E';   // 站立：只能在地面(.、X、O)，不能在玻璃 E 上
    if (lie == 1)
        return y + 1 < m && g[x][y] != '#' && g[x][y+1] != '#';   // 横躺：两格都不是空地 #
    return x + 1 < n && g[x][y] != '#' && g[x+1][y] != '#';       // 竖躺：两格都不是空地 #
}

// BFS 求最少操作数，不可达返回 -1
int bfs(int sx, int sy, int slie) {
    memset(dist, -1, sizeof(dist));
    queue<State> q;
    q.push({sx, sy, slie});
    dist[slie][sx][sy] = 0;
    while (!q.empty()) {
        State s = q.front(); q.pop();
        int x = s.x, y = s.y, lie = s.lie;
        if (lie == 0 && g[x][y] == 'O') return dist[lie][x][y];   // 目标：竖放在 O 上
        for (int d = 0; d < 4; d++) {
            int nx = x + nxt[lie][d][0];      // 滚动后的新位置
            int ny = y + nxt[lie][d][1];
            int nlie = nxt[lie][d][2];        // 滚动后的新姿态
            if (!valid(nx, ny, nlie)) continue;        // 放不住 → 跳过
            if (dist[nlie][nx][ny] != -1) continue;    // 已访问 → 跳过
            dist[nlie][nx][ny] = dist[lie][x][y] + 1;
            q.push({nx, ny, nlie});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        // 找到初始 X（一个 X = 竖放；相邻两个 X = 平放）
        int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
        for (int i = 0; i < n; i++) {
            cin >> g[i];
            for (int j = 0; j < m; j++)
                if (g[i][j] == 'X') {
                    if (x1 == -1) { x1 = i; y1 = j; }
                    else { x2 = i; y2 = j; }
                }
        }
        int sx, sy, slie;
        if (x2 == -1) { sx = x1; sy = y1; slie = 0; }          // 一个 X：竖放
        else if (x1 == x2) { sx = x1; sy = min(y1, y2); slie = 1; } // 同行：横躺，取左格
        else { sx = min(x1, x2); sy = y1; slie = 2; }          // 同列：竖躺，取上格
        cout << bfs(sx, sy, slie) << '\n';
    }
    return 0;
}
