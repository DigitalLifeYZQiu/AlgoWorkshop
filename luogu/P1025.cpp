//
// Created by robin chen on 24-9-25.
//
#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n,k;//n分成k份
	cin>>n>>k;
	vector<vector<int>> dp(201,vector<int>(7,0));
	for(int i=1;i<=n;i++) {
		dp[i][1]=1;
		dp[i][0]=1;
	}
	for(int x=2;x<=k;x++) {
		dp[1][x]=0;
		dp[0][x]=0;
	}
	for(int i=2;i<=n;i++) {
		for(int x=2;x<=k;x++) {
			if(i>x) dp[i][x] = dp[i-1][x-1] + dp[i-x][x];
			else dp[i][x] = dp[i-1][x-1];
		}
	}
	cout<<dp[n][k]<<endl;
	return 0;
}
