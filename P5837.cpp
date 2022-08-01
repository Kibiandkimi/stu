//
// Created by kibi on 2021/8/17.
//
#include <bits/stdc++.h>
using namespace std;
int m,n,r[1005][1005][2],vis[1005];
double a[1005][1005];
//struct node{
//    int s;
//    int last;
//};
int s[1005];
priority_queue<pair<int,int> > q;
int d(int x){
    for(int i = 1; i <= n; i++){
        s[i] = 1e9;
        vis[i] = 0;
    }
    s[1] = 0;
    q.push(make_pair(0,1));
    while(!q.empty()){
        int t = q.top().second;
        q.pop();
        if(vis[t])continue;
        vis[t] = 1;
        for(int i = 1; i <= n; i++){
            if(r[t][i][0]!=0){
                if(r[t][i][0]+s[t]<s[i]&&r[t][i][1]>=x){
                    s[i] = r[t][i][0]+s[t];
                    //                    s[i].last = t;
                    q.push(make_pair(-s[i], i));
                }
            }
        }
    }
    return s[n];
}
vector<int> t;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int aa,b, w, v;
        scanf("%d %d %d %d", &aa, &b, &w, &v);
        r[aa][b][0] = r[b][aa][0] = w;
        r[aa][b][1] = r[b][aa][1] = v;
        a[aa][b] = a[b][aa] = v /(double) w;
        t.push_back(v);
    }
    //    int sum1 = 0, sum2 = 1e9;
    int mx = 0;
    for(int i = 1; i <= m; i++){
        mx = max(mx, t[i-1]*(1000000)/d(t[i-1]));
    }
    printf("%d",mx);
}