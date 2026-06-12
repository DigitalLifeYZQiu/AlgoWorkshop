//
// Created by Yunzhong Qiu on 2024/12/11.
//

#include<iostream>
#include<vector>
using namespace std;


int main() {
    int n; // checkpoint num
    int m; // road num
    cin>>n;
    vector<int>checkpoint (n,0);
    for(int i=0;i<n;i++){cin>>checkpoint[i];}
    cin>>m;
    vector<vector<int>> road(m, vector<int>(2,0));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<2;j++)
        {
            cin>>road[i][j];
        }
    }


    return 0;
}