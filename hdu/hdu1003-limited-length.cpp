//
// Created by robin chen on 24-10-3.
//
#include<iostream>
#include<deque>
using namespace std;

deque<int> dq;

int s[100005];

int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>s[i];
	}
	for(int i=1;i<=n;i++) {
		s[i] = s[i] + s[i-1];
	}
	int ans = -1e8;
	dq.push_back(0);
	for(int i=1;i<=n;i++) {
		while(!dq.empty() && dq.front()<i-m)dq.pop_front();//队头超过m范围：删头
		if(dq.empty()) ans = max(ans,s[i]);
		else ans = max(ans, s[i] - s[dq.front()]);//队头就是最小的s[k]
		while(!dq.empty() && s[dq.back()] >= s[i]) dq.pop_back();//队尾大于s[i]，去尾
		dq.push_back(i);
	}
	cout<<ans<<endl;
	return 0;
}