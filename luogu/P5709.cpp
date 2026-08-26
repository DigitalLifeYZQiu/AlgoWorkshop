//
// Created by Yunzhong Qiu on 2026/6/16.
//

#include<iostream>
using namespace std;
int m,t,s;
int main()
{
    cin>>m>>t>>s;
    if (t==0)
    {
        cout<<0<<endl;
        return 0;
    }
    if (s%t==0)
    {
        if (m-s/t >= 0)
        {
            cout<<m-s/t<<endl;
        }
        else
        {
            cout<<0<<endl;
        }
    }
    else
    {
        if (m-s/t-1>=0)
        {
            cout<<m-s/t-1<<endl;
        }
        else
        {
            cout<<0<<endl;
        }
    }
    return 0;
}