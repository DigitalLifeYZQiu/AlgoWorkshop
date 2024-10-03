//
// Created by robin chen on 24-9-25.
//
#include<iostream>
#include<queue>
using namespace std;
int Hash[1003]={0};//用哈希检查内存中有没有单词，hash[i]=1表示单词i在内存中
queue<int> mem;
int main(){
	int m,n;
	cin>>m>>n;
	int cnt=0;//查字典次数
	while(n--) {
		int en;
		cin>>en;
		if(!Hash[en]) {
			++cnt;
			mem.push(en);
			Hash[en] = 1;
			while(mem.size()>m){ //内存满了
				Hash[mem.front()]=0;
				mem.pop();
			}
		}
	}
	cout<<cnt;
	return 0;
}