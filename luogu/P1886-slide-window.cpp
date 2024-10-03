//
// Created by robin chen on 24-10-2.
//
#include<iostream>
#include<deque>
using namespace std;

const int N = 1000005;
int a[N];
deque<int> q;

int main() {
	int n, m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
	}
	for(int i=1;i<=n;i++) {//输出最小值
		while(!q.empty() && a[q.back()] > a[i])q.pop_back();//去尾
		q.push_back(i);
		if(i>=m) {
			while(!q.empty() && q.front()<=i-m)q.pop_front();//删头
			cout<<a[q.front()]<< " ";
		}
	}
	cout<<endl;
	while(!q.empty())q.pop_front();
	for(int i=1;i<=n;i++) {
		while(!q.empty() && a[q.back()]<a[i])q.pop_back();
		q.push_back(i);
		if(i>=m) {
			while(!q.empty() && q.front()<=i-m)q.pop_front();
			cout<<a[q.front()]<< " ";
		}
	}
	cout<<endl;
	return 0;
}