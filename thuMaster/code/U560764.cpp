//
// Created by Yunzhong Qiu on 2026/8/27.
//
// 洛谷 U560764 Binary Matrix
// 题意：给定 n×m 的 0/1 矩阵 A，求把 A 翻转若干格（0<->1）得到矩阵 B，
//       使 B 每行、每列的异或和都为 0，最小化翻转次数。
// 思路：翻转 (i,j) 会同时翻转"第 i 行的异或和"和"第 j 列的异或和"的奇偶性。
//       设 R = 异或和为 1 的行数，C = 异或和为 1 的列数，则答案为 max(R, C)。
//       （下界：每个奇行/奇列至少需要 1 次翻转；上界：可构造恰好 max(R,C) 次。）
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;

        vector<string> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        // 统计异或和为 1 的行数 R
        int R = 0;
        for (int i = 0; i < n; i++)
        {
            int x = 0;
            for (int j = 0; j < m; j++) x ^= (a[i][j] - '0');   // 整行异或
            if (x) R++;                                          // 行异或为 1
        }

        // 统计异或和为 1 的列数 C
        int C = 0;
        for (int j = 0; j < m; j++)
        {
            int x = 0;
            for (int i = 0; i < n; i++) x ^= (a[i][j] - '0');   // 整列异或
            if (x) C++;                                          // 列异或为 1
        }

        cout << max(R, C) << '\n';
    }
    return 0;
}
