//
// Created by robin chen on 24-9-5.
//

//
// Created by robin chen on 24-9-3.
//
#include<iostream>
using namespace std;
const int N = 105;
struct node{
	int id,nextid;
	//int data;
}nodes[N];

int main(){
	int n,m;
	cin>>n>>m;
	nodes[0].nextid = 1;
	for(int i=1;i<=n;i++){
		nodes[i].id = i;
		nodes[i].nextid = i+1;
	}
	nodes[n].nextid = 1;
	int now = 1, prev = 1;
	while((n--)>1){
		for(int i=1;i<m;i++){
			prev = now;
			now = nodes[now].nextid;
		}
		cout<<nodes[now].id<<" ";
		nodes[prev].nextid = nodes[now].nextid;
		now = nodes[prev].nextid;
	}
	cout<<nodes[now].nextid;
	return 0;
}
