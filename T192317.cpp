//
// Created by kibi on 2021/8/8.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,vis[100005],r[100005];

vector<int> a[100005];
struct node{
    int a1,a2;
    node operator+(const node& a){
        node t;
        t.a1 = a1 + a.a1;
        t.a2 = a2 + a.a2;
        return t;
    }
};
node d[100005];
node f(int x){
    if(vis[x])return node({0,0});
    vis[x] = 1;
    int flag = 0;
    for(int i : a[x]){
        if(r[i]){
            flag = r[i];
            break;
        }
    }
    r[x] = flag==1?2:1;
    if(r[x]==1){
        d[x].a1 = 1;
        d[x].a2 = 0;
    }else{
        d[x].a1 = 0;
        d[x].a2 = 1;
    }
    for(int i : a[x]){
        d[x] = d[x] + f(i);
    }
    return d[x];
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    int s = 0;
    //    int ls = 1;
    for(int i = 1; i <= n; i++){
        if(!vis[i]) {
            node t = f(i);
            s += min(t.a1, t.a2);
        }
    }
    cout << s;
}