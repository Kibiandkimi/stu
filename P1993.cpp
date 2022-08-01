//
// Created by kibi on 2021/8/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,d[5005],vis[5005],s[5005];
struct node{
    int v,w;
};
vector<node> a[5005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int t,aa,b,c;
        scanf("%d %d %d", &t, &aa, &b);
        switch(t){
            case 1:scanf("%d", &c);a[b].push_back(node({aa,-c}));break;
            case 2:scanf("%d", &c);a[aa].push_back(node({b,c}));break;
            case 3:a[aa].push_back(node({b,0}));a[b].push_back(node({aa,0}));break;
        }
    }
    for(int i = 1; i <= n; i++){
        d[i] = 1e9;
        a[0].push_back(node({i,0}));
    }
    d[0] = 0;
    vis[0] = 1;
    // s[1] = 1;
    queue<int> q;
    q.push(0);
    bool flag = true;
    while(!q.empty()){
        int t = q.front();
        s[t]++;
        if(s[t] > n){
            flag = false;
            break;
        }
        q.pop();
        vis[t] = 0;
        int sa = a[t].size();
        for(int i = 0; i < sa; i++){
            if(d[a[t][i].v]>d[t]+a[t][i].w){
                d[a[t][i].v] = d[t]+a[t][i].w;
                if(!vis[a[t][i].v]){
                    q.push(a[t][i].v);
                    vis[a[t][i].v] = 1;
                }
            }
        }
    }
    if(flag){
        cout << "Yes";
    }else{
        cout << "No";
    }
}