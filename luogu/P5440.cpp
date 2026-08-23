//
// Created by Yunzhong Qiu on 2026/8/22.
//
// 洛谷 P5440 【XR-2】奇迹
// 题意：8 位日期 YYYYMMDD，其中若干位是 '-'（未知）。求有多少种填法使得：
//       (1) 日期合法（月 1~12、日在当月范围内、闰年 2 月、年 1~9999）；
//       (2) 由"日"组成的 2 位数、由"月+日"组成的 4 位数、由"年+月+日"组成的 8 位数均为质数。
// 思路：按位 DFS（从日往年到，低位到高位），每填完一段就剪枝；欧拉筛预先生成小质数，
//       判断大数是否为质数时用试除。
//

#include <iostream>
#include <string>

using namespace std;

// ---------- 欧拉筛：筛出 [2, 100000] 的质数（sqrt(1e8) ≈ 1e4，多筛一点保险） ----------
const int MAXN = 100005;
int prime[MAXN], tot;      // prime 存质数，tot 是质数个数
bool isComp[MAXN];         // isComp[i]：i 是否为合数

void sieve()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!isComp[i]) prime[tot++] = i;               // i 是质数，存入 prime
        for (int j = 0; j < tot && (long long)i * prime[j] < MAXN; j++)
        {
            isComp[i * prime[j]] = true;                // 用最小质因子筛掉合数
            if (i % prime[j] == 0) break;               // 保证每个合数只被筛一次
        }
    }
}

// 试除法判质数：用筛出的小质数去试除到 sqrt(x)
bool isPrime(int x)
{
    if (x < 2) return false;
    for (int i = 0; i < tot && (long long)prime[i] * prime[i] <= x; i++)
        if (x % prime[i] == 0) return x == prime[i];    // 恰好等于它自己才是质数
    return true;
}

// 闰年判断
bool isLeap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

// bigMonth[m]：m 月是否有 31 天（下标 1..12）
bool bigMonth[13] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};

// p10[k] = 10^k，用于按位拼数
int p10[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

int a[9];   // a[1..8]：日期各位数字，-1 表示该位是 '-'

// 从低位往高位枚举：nown 从 8（日个位）到 1（年千位）
// num：已填的低位组成的数
// needLeap：当前日期是否必须是闰年（出现了 2 月 29 号）
// need31：日是否为 31（要求月份必须是大月）
int dfs(int nown, int num, bool needLeap, bool need31)
{
    if (nown == 0)                                  // 8 位全部填完
    {
        int year = num / 10000;
        if (year == 0) return 0;                    // 年必须是 1..9999
        if (needLeap && !isLeap(year)) return 0;    // 2 月 29 号必须是闰年
        return isPrime(num);                        // 8 位数必须是质数
    }
    if (nown == 6)                                  // 已填完"日"（低 2 位）
    {
        if (num == 0 || num > 31 || !isPrime(num)) return 0;  // 日须是 1..31 的质数
        if (num == 31) need31 = true;               // 31 号必须是大月
    }
    if (nown == 4)                                  // 已填完"月+日"（低 4 位）
    {
        if (num < 32 || num > 1231 || !isPrime(num)) return 0; // 月+日须为质数且月合法
        int month = num / 100, day = num % 100;
        if (need31 && !bigMonth[month]) return 0;   // 31 号必须是大月
        if (month == 2)
        {
            if (day > 29) return 0;                 // 2 月最多 29 天
            if (day == 29) needLeap = true;         // 2 月 29 号必须是闰年
        }
    }

    if (a[nown] != -1)                              // 该位已给定，直接填入
        return dfs(nown - 1, a[nown] * p10[8 - nown] + num, needLeap, need31);

    int res = 0;
    for (int d = 0; d <= 9; d++)                    // 该位是 '-'，枚举 0~9
        res += dfs(nown - 1, d * p10[8 - nown] + num, needLeap, need31);
    return res;
}

int main()
{
    sieve();

    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        for (int i = 1; i <= 8; i++)
            a[i] = (s[i - 1] == '-' ? -1 : s[i - 1] - '0');
        cout << dfs(8, 0, false, false) << '\n';
    }
    return 0;
}
