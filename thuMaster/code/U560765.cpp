//
// Created by Yunzhong Qiu on 2026/8/27.
//
// 洛谷 U560765 Floor or Ceil
// 题意：对整数 x 进行恰好 n 次「下取整除以 2」和 m 次「上取整除以 2」，
//       顺序任意，求 n+m 次操作后 x 的最小值与最大值。
// 结论（已对拍验证）：
//   min = floor( ceil(x / 2^m) / 2^n )   （先把 m 次上取整做完，再做 n 次下取整）
//   max = ceil( floor(x / 2^n) / 2^m )   （先把 n 次下取整做完，再做 m 次上取整）
// 注意：x <= 1e9 < 2^30，n,m 可达 1e9，需对"除 2^c"做 31 次封顶，避免溢出。
//

#include <iostream>

using namespace std;

// floor(x / 2^c)，c 很大时结果为 0
long long floor_div2(long long x, long long c)
{
    if (c >= 31) return 0;       // x < 2^30，右移 >=30 位必为 0
    return x >> c;
}

// ceil(x / 2^c)
long long ceil_div2(long long x, long long c)
{
    if (x == 0) return 0;
    if (c >= 31) return 1;       // 0 < x < 2^30 <= 2^c，上取整为 1
    return (x + ((1LL << c) - 1)) >> c;   // (x + 2^c - 1) / 2^c
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        long long x, n, m;
        cin >> x >> n >> m;

        long long mn = floor_div2(ceil_div2(x, m), n);   // 最小：先 ceil 后 floor
        long long mx = ceil_div2(floor_div2(x, n), m);   // 最大：先 floor 后 ceil

        cout << mn << ' ' << mx << '\n';
    }
    return 0;
}
