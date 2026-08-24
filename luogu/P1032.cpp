//
// Created by Yunzhong Qiu on 2026/8/24.
//
// 洛谷 P1032 [NOIP 2002 提高组] 字串变换
// 题意：给定字符串 A、B 和最多 6 条变换规则 Ai->Bi（子串 Ai 替换为 Bi），
//       求 A 变成 B 的最少变换步数；10 步内无法完成输出 "NO ANSWER!"。
// 思路：状态 = 字符串，一步变换 = 一条边（权 1），用 BFS 求最少步数；
//       用 map 去重，避免规则环造成死循环。
//

#include<iostream>
#include<queue>
#include<map>
#include<string>

using namespace std;

string A,B;
string from[7], to[7];   // 变换规则，至多 6 条
int cnt=0;               // 实际读到的规则条数

// BFS 求最少变换步数，10 步内不可达返回 -1
int bfs()
{
    queue<pair<string, int>> q;
    map<string, int> step;          // step[s]：第一次到达字符串 s 的步数（用于去重）

    q.push({A, 0});
    step[A] = 0;

    while (!q.empty())
    {
        string s = q.front().first;
        int d = q.front().second;
        q.pop();

        if (s == B) return d;       // 找到目标，d 就是最少步数
        if (d >= 10) continue;      // 已达 10 步，不能再往下变换

        for (int i=0; i<cnt; i++)
        {
            // 枚举规则 from[i] 在 s 中出现的每个位置（含重叠）
            size_t pos = 0;
            while ((pos = s.find(from[i], pos)) != string::npos)
            {
                string t = s;
                t.replace(pos, from[i].size(), to[i]);   // 在 pos 处把 from[i] 换成 to[i]
                if (!step.count(t))                      // 未访问过才入队
                {
                    step[t] = d+1;
                    q.push({t, d+1});
                }
                pos++;               // 前进一步，找下一个出现位置（保证重叠也找到）
            }
        }

    }
    return -1;                       // 队列清空仍未到达 B
}

int main()
{
    cin>>A>>B;
    string a, b;
    while (cin>>a>>b)                // 规则读入到 EOF 为止（规则数不显式给出）
    {
        from[cnt] = a;
        to[cnt] = b;
        cnt++;
    }
    int ans = bfs();
    if (ans == -1) cout<<"NO ANSWER!"<<endl;
    else cout<<ans<<endl;
    return 0;
}
