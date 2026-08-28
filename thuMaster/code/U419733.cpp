//
// Created by Yunzhong Qiu on 2026/8/28.
//
// 洛谷 U419733 井字井字棋（Ultimate Tic-Tac-Toe）
// 题意：9×9 棋盘 = 3×3 个大格，每个大格内 3×3 个小格。双方轮流落子，
//       按"小格三连占领大格，大格三连获胜"的规则判断棋谱是否合法、是否分胜负。
// 思路：逐步模拟棋谱，每步做「合法性检查 → 落子 → 更新大格占领 → 判断胜负/满盘」。
//

#include <iostream>

using namespace std;

int board[10][10];   // board[大格编号][小格编号]：0 空，1 先手，2 后手
int bigCap[10];      // 大格占领情况：0 未占领，1 先手，2 后手

// 3×3 网格的三连判断：返回获胜方(1/2)，无则返回 0
// （横、竖、两条对角线）
int win3(int g[3][3])
{
    for (int r = 0; r < 3; r++)
        if (g[r][0] && g[r][0] == g[r][1] && g[r][1] == g[r][2]) return g[r][0];
    for (int c = 0; c < 3; c++)
        if (g[0][c] && g[0][c] == g[1][c] && g[1][c] == g[2][c]) return g[0][c];
    if (g[0][0] && g[0][0] == g[1][1] && g[1][1] == g[2][2]) return g[0][0];
    if (g[0][2] && g[0][2] == g[1][1] && g[1][1] == g[2][0]) return g[0][2];
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int A[82], B[82];                    // 棋谱：A[k]=大格，B[k]=小格
    for (int k = 1; k <= n; k++) cin >> A[k] >> B[k];

    for (int k = 1; k <= n; k++)
    {
        int a = A[k], b = B[k];
        int p = (k % 2 == 1) ? 1 : 2;    // 奇数步先手，偶数步后手

        // ---------- 合法性检查 ----------
        bool ill = false;
        if (board[a][b] != 0) ill = true;              // ① 该小格已有棋子
        else if (bigCap[a] != 0) ill = true;           // ② 该大格已被占领
        else if (k == 1 && a == 5 && b == 5) ill = true; // ③ 第一步不能下中心 (5,5)
        else if (k > 1)
        {
            int pb = B[k - 1];                         // 上一步的小格编号
            // ④ 若编号为 pb 的大格未占领，则本步必须下在该大格
            if (bigCap[pb] == 0 && a != pb) ill = true;
        }
        if (ill)
        {
            cout << "illegal\n" << k << '\n';
            return 0;
        }

        // ---------- 落子 ----------
        board[a][b] = p;

        // ---------- 判断大格 a 是否被占领 ----------
        int g[3][3];
        for (int s = 1; s <= 9; s++)
            g[(s - 1) / 3][(s - 1) % 3] = board[a][s];   // 小格编号转 3×3 坐标
        int bw = win3(g);
        if (bw) bigCap[a] = bw;

        // ---------- 判断整个棋盘是否获胜（大格三连） ----------
        int gg[3][3];
        for (int i = 1; i <= 9; i++)
            gg[(i - 1) / 3][(i - 1) % 3] = bigCap[i];
        int ww = win3(gg);
        if (ww)
        {
            cout << (ww == 1 ? "first" : "second") << '\n' << k << '\n';
            return 0;
        }

        // ---------- 判断棋盘是否已满（平局判定） ----------
        bool full = true;
        for (int i = 1; i <= 9 && full; i++)
            if (bigCap[i] == 0)
                for (int j = 1; j <= 9; j++)
                    if (board[i][j] == 0) { full = false; break; }
        if (full)
        {
            int cntBig[3] = {0, 0, 0}, cntSmall[3] = {0, 0, 0};
            for (int i = 1; i <= 9; i++) cntBig[bigCap[i]]++;        // 占领的大格数
            for (int i = 1; i <= 9; i++)
                if (bigCap[i] == 0)
                    for (int j = 1; j <= 9; j++)
                        if (board[i][j]) cntSmall[board[i][j]]++;    // 未占领大格里的落子数
            int w;
            if (cntBig[1] != cntBig[2]) w = (cntBig[1] > cntBig[2]) ? 1 : 2;
            else w = (cntSmall[1] > cntSmall[2]) ? 1 : 2;
            cout << (w == 1 ? "first" : "second") << '\n' << k << '\n';
            return 0;
        }
    }

    cout << "to be continued\n";
    return 0;
}
