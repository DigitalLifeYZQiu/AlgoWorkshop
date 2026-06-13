//
// Created by Yunzhong Qiu on 2026/6/12.
//

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
    double a, b, c;
    double space, p;
    cin>>a>>b>>c;
    p=(a+b+c)/2;
    space=sqrt(p*(p-a)*(p-b)*(p-c));
    cout<<fixed<<setprecision(1)<<space<<endl;
    return 0;
}