//
// Created by robin chen on 24-9-27.
//

#include<iostream>
#include<cmath>
using namespace std;
typedef unsigned long long ull;

int LEN(ull n) {
	//计算n的位数
	int cnt=0;
	while(n) {
		cnt++;
		n/=10;
	}
	return cnt;
}

ull f(ull n) {
	//f(x)反转函数
	ull ans=0;
	while(n) {
		ans = ans*10+ (n%10);
		n/=10;
	}
	return ans;
}

void solve() {
	ull n,minn = 9e18;
	cin>>n;
	int len = LEN(n);
	for(int i=0;i<=len;i++) {
		// cout<<endl;
		// cout<<"i="<<i<<endl;
		ull p = pow(10,(ull)i);	//第i位加1
		// cout<<"p="<<p<<endl;
		// cout<<"n%p="<<n%p<<endl;
		ull ni = n-(n%p) + p;		//后面的位全部变成0
		// cout<<"ni="<<ni<<endl;
		if(ni % 10 ==0)ni++;
		minn = min(minn,f(ni));
		// cout<<"minn="<<minn<<endl;
		// cout<<"f(ni)"<<f(ni)<<endl;
	}
	cout<<minn-1<<endl;
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}