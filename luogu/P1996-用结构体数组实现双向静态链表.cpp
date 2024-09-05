//
// Created by robin chen on 24-9-5.
//

#include <iostream>
using namespace std;
const int N = 105;
struct node{
  int id;
  //int data;
  int preid, nextid;
 }nodes[N];

 int main() {
     int n, m;
     cin>>n>>m;
     nodes[0].nextid = 1;
     for(int i=1; i<=n; i++) {
         nodes[i].id = i;
         nodes[i].preid = i-1;
         nodes[i].nextid = i+1;
     }
     nodes[n].nextid = 1;
     nodes[1].preid = n;
     int now = 1;
     while((n--)>1) {
         for(int i=1;i<m;i++) {
             now = nodes[now].nextid;
         }
         cout<<nodes[now].id<<" ";
         int prev = nodes[now].preid, next = nodes[now].nextid;
         nodes[prev].nextid = nodes[now].nextid;
         nodes[next].preid = nodes[now].preid;
         now = next;
     }
     cout<<nodes[now].nextid<<endl;
     return 0;
 }