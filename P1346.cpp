//
// Created by kibi on 2021/10/13.
//
#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int ck[105], vis[105], d[105];
priority_queue<pair<int, int> > q;
vector<int> e[105];
int main(){
    scanf("%d %d %d", &n, &a, &b);
    for(int i = 1; i <= n; i++){
        int k;
        scanf("%d", &k);
        while(k--){
            int t;
            scanf("%d", &t);
            e[i].push_back(t);
        }
    }
    for(int i = 1; i <= n; i++){
        d[i] = 1e9;
    }
    d[a] = 0;
    q.push({0, a});
    while(!q.empty()){
        int t = -q.top().first, x = q.top().second;
        q.pop();
        if(vis[x]){
            continue;
        }
        if(x == b){
            printf("%d", t);
            return 0;
        }
        vis[x] = 1;
        int sa = e[x].size();
        for(int i = 0; i < sa; i++){
            if(d[e[x][i]]>(t+(i!=0))){
                d[e[x][i]] = (t+(i!=0));
                q.push({-d[e[x][i]], e[x][i]});
            }
        }
    }
    printf("-1");
}