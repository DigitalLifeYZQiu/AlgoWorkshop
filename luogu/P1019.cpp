//
// Created by Yunzhong Qiu on 2026/8/21.
//
// 洛谷 P1019 单词接龙（NOIP 2000 提高组）
// 题意：给定 n 个单词和一个起始字母，求以该字母开头、每个单词最多使用 2 次、
//       相邻单词首尾重合拼接（重合部分合并）而成的"龙"的最大长度。
// 思路：预处理 overlap[i][j]（i 接 j 的最短合法重合长度） + DFS 回溯枚举拼接顺序。
//

#include<iostream>
#include<cstring>

using namespace std;

string words[25];   // 单词表，n <= 20，开 25 保险
int n, ans;         // n：单词个数；ans：龙的最大长度
int overlap[25][25]; // overlap[i][j]：单词 i 接在单词 j 前面时的最短合法重合长度，-1 表示不可接
int used[25];        // used[i]：单词 i 在当前的龙中已被使用的次数（最多 2 次）

// 计算单词 i 接在单词 j 前面时的最短合法重合长度
// 规则：word[i] 的后 k 个字符必须等于 word[j] 的前 k 个字符（k >= 1），
//       且 k 必须小于两个单词各自的长度（防止完全包含，如 at 与 atide 不能相连）。
int calc_overlap(int i, int j)
{
    int li = words[i].size(), lj = words[j].size();
    // 从 k=1 开始从小到大枚举重合长度，找到的第一个 k 就是最短合法重合
    // （重合越短，龙的总长度越长；且重合长短不影响后续还能接什么单词）
    for (int k=1; k<min(li, lj); k++)
    {
        if (words[i].substr(li - k) == words[j].substr(0, k))
        {
            return k;   // 找到最短合法重合长度，直接返回
        }
    }
    return -1;          // 没有任何合法重合，i 不能接在 j 前面
}

// DFS 回溯：当前龙的最后一个单词是 last，龙当前总长度为 cur
void dfs(int last, int cur)
{
    ans = max(ans, cur);        // 龙可以在任意时刻停下，随时更新答案

    // 枚举下一个要接的单词 j
    for (int j=0; j<n; j++)
    {
        // 剪枝：单词 j 已用满 2 次，或 last 无法接到 j，跳过
        if (used[j] >= 2 || overlap[last][j] == -1) continue;

        used[j]++;              // 使用单词 j（回溯：进入递归前"标记"）
        // 接上 j 后新增长度 = j 的长度 - 与 last 重合的部分
        dfs(j, cur + (int)words[j].size() - overlap[last][j]);
        used[j]--;              // 回溯：退出递归后"撤销标记"
    }
}

int main()
{
    // ---------- 输入 ----------
    cin>>n;
    for (int i=0; i<n; i++)
    {
        cin>>words[i];          // 读入 n 个单词
    }
    char start; cin>>start;     // 读入龙开头的字母

    // ---------- 预处理：计算所有有序单词对 (i, j) 的重合长度 ----------
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            overlap[i][j] = calc_overlap(i, j);
        }
    }

    // ---------- DFS：枚举龙的第一个单词 ----------
    for (int i=0; i<n; i++)
    {
        if (words[i][0] == start)   // 第一个单词必须以起始字母开头
        {
            used[i] = 1;            // 第一个单词已使用 1 次
            dfs(i, words[i].size()); // 龙的初始长度就是该单词的长度
            used[i] = 0;            // 回溯，尝试其他起点
        }
    }

    cout<<ans<<endl;
    return 0;
}
