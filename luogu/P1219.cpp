//
// P1219 [USACO1.5] 八皇后 Checker Challenge
// 经典 N 皇后问题：使用 DFS + 回溯，逐行放置棋子。
//

#include<bits/stdc++.h>
using namespace std;

// n   : 棋盘大小，棋盘为 n x n
// cnt : 已经找到的合法解的总数
int n, cnt;

// ans[r] 表示第 r 行的棋子放在第 ans[r] 列。
// 本题只使用下标 1 到 n，下标 0 不使用。
int ans[20];

// col[c]  : 第 c 列是否已经被占用
// d1[idx] : 左上到右下方向的斜线是否已经被占用，使用 r - c + n 作为编号
// d2[idx] : 右上到左下方向的斜线是否已经被占用，使用 r + c 作为编号
bool col[20], d1[40], d2[40];

void dfs(int r) {
    // 已经成功放完前 n 行，说明找到了一个合法解
    if (r > n) {
        cnt++;  // 解的总数加 1

        // 题目只要求输出前 3 个解
        if (cnt <= 3) {
            // 输出第 1 行到第 n 行的棋子列号
            for (int i = 1; i <= n; i++) {
                // 每行的最后一个数字后面换行，其余数字后面加空格
                cout << ans[i] << (i == n ? '\n' : ' ');
            }
        }
        return;
    }

    // 尝试把第 r 行的棋子放在第 c 列
    for (int c = 1; c <= n; c++) {
        // 如果当前列被占用，或者两条斜线之一被占用，则跳过
        if (col[c] || d1[r - c + n] || d2[r + c]) continue;

        // 记录第 r 行棋子的列号
        ans[r] = c;

        // 标记当前列和两条斜线，表示这些位置后续不能再放棋子
        col[c] = d1[r - c + n] = d2[r + c] = true;

        // 递归搜索下一行
        dfs(r + 1);

        // 回溯：撤销当前选择，恢复状态，继续尝试下一列
        col[c] = d1[r - c + n] = d2[r + c] = false;
    }
}

int main() {
    cin >> n;

    // 从第 1 行开始深度优先搜索
    dfs(1);

    // 搜索结束后输出解的总数
    cout << cnt << endl;
    return 0;
}
