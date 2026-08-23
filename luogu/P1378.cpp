//
// Created by Yunzhong Qiu on 2026/8/23.
//
// 洛谷 P1378 油滴扩展
// 题意：长方形盒子里有 N(N<=6) 个点，依次在点上放油滴，油滴扩展成圆，
//       直到碰到盒子边界或已放好的油滴。求覆盖面积最大时剩余的面积（四舍五入）。
// 思路：N<=6，直接 DFS 枚举所有放置顺序（排列型搜索）；每次放置时模拟计算
//       该油滴的最大半径 = min(到四边距离, 到各已放油滴的距离 - 其半径)。
//

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);   // 精确的 π

int n;
double X1, Y1, X2, Y2;          // 矩形两个对角顶点（顺序未知，可能有负数）
double x[7], y[7];              // 油滴坐标（N <= 6）
double r[7];                    // 已放油滴的半径
bool used[7];                   // 该油滴是否已经放置
double ans;                     // 覆盖的最大面积

// 计算第 i 个油滴当前能扩展到的最大半径
double calcR(int i)
{
    // 到矩形四条边的距离（对 X1/X2、Y1/Y2 都取绝对值再取 min，
    // 天然覆盖左右上下四堵墙，无需关心哪个角是左上）
    double res = min({fabs(x[i] - X1), fabs(x[i] - X2),
                      fabs(y[i] - Y1), fabs(y[i] - Y2)});

    // 到每个已放油滴的约束：圆之间不能重叠，r_i <= 圆心距 - r_j
    for (int j = 0; j < n; j++)
    {
        if (!used[j]) continue;
        double d = hypot(x[i] - x[j], y[i] - y[j]);   // 两圆心距离
        res = min(res, d - r[j]);
    }
    return max(0.0, res);        // 若圆心已被其他圆覆盖，半径为 0
}

// cnt：已放油滴数；sum：当前已覆盖面积
void dfs(int cnt, double sum)
{
    ans = max(ans, sum);         // 覆盖面积单调不减，随时更新最大

    for (int i = 0; i < n; i++)
    {
        if (used[i]) continue;
        r[i] = calcR(i);         // 做选择：确定这个油滴的半径
        used[i] = true;
        dfs(cnt + 1, sum + PI * r[i] * r[i]);   // 累加圆面积
        used[i] = false;         // 回溯：撤销，供其他顺序使用
    }
}

int main()
{
    cin >> n;
    cin >> X1 >> Y1 >> X2 >> Y2;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    dfs(0, 0);

    double boxArea = fabs(X1 - X2) * fabs(Y1 - Y2);   // 盒子面积
    cout << (int)(boxArea - ans + 0.5) << endl;       // 剩余面积，四舍五入
    return 0;
}
