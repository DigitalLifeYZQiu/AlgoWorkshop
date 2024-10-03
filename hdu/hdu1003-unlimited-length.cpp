//
// Created by robin chen on 24-10-3.
//

#include<iostream>
using namespace  std;
int dp[100005];//dp[i]为以第i个数结尾的最大值
int main() {
	int t;
	cin>>t;
	for(int k=1;k<=t;k++) {
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) {
			cin>>dp[i];//用dp[]存储数据a[]
		}
		int start = 1, end = 1, p = 1;//起点，重点，扫描位置
		int maxsum = dp[1];
		for(int i=2;i<=n;i++) {
			if(dp[i-1] + dp[i] >= dp[i]) {//转移方程dp[i]=max(dp[i-1]+a[i], a[i])
				dp[i] = dp[i-1] + dp[i];//dp[i-1]+a[i]比a[i]大
			}
			else {//a[i]更大，那么dp[i]就是a[i]
				p = i;
			}
			if(dp[i] > maxsum) {//dp[i]是一个更大的子序和
				maxsum = dp[i];
				start = p;//以p为开始
				end = i;//以i为结尾
			}
		}
		cout<<"Case "<<k<<":"<<endl;
		cout<<maxsum<<" "<<start<<" "<<end<<" "<<endl;
		if(k!=t)cout<<endl;
	}

}