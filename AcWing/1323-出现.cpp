//
// Created by Yunzhong Qiu on 2026/5/6.
//

//#include<bits/stdc++.h>
#include<iostream>
#include<set>
using namespace std;
int num;
set<int> s;
set<int>::iterator it;
int main()
{
    int n, top = 0;
    cin>>n;
    int a[n];
    for (int i=1; i<=n; i++)
    {
        cin>>num;
        s.insert(num);
    }
    for (it = s.begin(); it!=s.end(); it++)
    {
        a[++top] = *it;
    }
    for (int i=0; i<=n; i++)
    {
        if (a[i+1] != i)
        {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}