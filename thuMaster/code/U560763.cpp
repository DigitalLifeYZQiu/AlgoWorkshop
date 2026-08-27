//
// Created by Yunzhong Qiu on 2026/8/27.
//
// 洛谷 U560763 Movie
// 题意：给定影片时长 "AB:CD:EF"（时:分:秒）和帧率 x（帧/秒），求影片总帧数。
// 思路：总帧数 = 总秒数 × x = (时×3600 + 分×60 + 秒) × x。
//

#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
    int T;
    cin>>T;                          // 测试数据组数
    while (T--)
    {
        int h, m, s, x;

        // 直接按 "时:分:秒 帧率" 的格式读入：
        // 格式串里的冒号是普通字符，要求输入里恰好是冒号；
        // %d 会自动跳过前导零（如 "06" 读成 6），也自动跳过空白。
        scanf("%d:%d:%d %d", &h, &m, &s, &x);

        // 换算成总秒数（用 3600LL / 60LL 保证按 long long 计算，避免乘法溢出）
        long long total = h * 3600LL + m * 60LL + s;

        cout<<total*x<<endl;          // 总帧数 = 总秒数 × 帧率
    }
    return 0;
}
