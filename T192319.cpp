//
// Created by kibi on 2021/8/8.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,k,sk,vis[2005],sta[2005],p;
struct node{
    int v,w;
};
vector<node> a[2005];
int f(int x, int s){
    if(x == n){
        int sm = m-s;
        int t = sk - sm;
        int tt[2005], ss = 0;
        for(int i = 1; i <= s; i++){
            tt[i] = sta[i];
        }
        sort(tt+1,tt+1+ ss);
        for(int i = t+1; i <= s; i++){
            ss += tt[i];
        }
        return ss;
    }
    int mn = 1e9;
    vis[x] = 1;
    p++;
    for(int i = 0; i < a[x].size(); i++){
        if(!vis[a[x][i].v]){
            sta[p] = a[x][i].w;
            mn = min(mn, f(a[x][i].v, s+1));
        }
    }
    vis[x] = 0;
    sta[p] = 0;
    p--;
    return mn;
}
int main(){
    cin >> n >> k >> m;
    sk = m-k;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back((node){v,w});
        a[v].push_back((node){u,w});
    }
    if(m-k==0){
        for(int i = 2; i <= n; i++){
            vis[i] = 1e9;
        }
        bool flag = true;
        while(flag){
            flag = false;
            for(int i = 1; i <= n; i++){
                for(int j = 0; j < a[i].size(); j++){
                    if(vis[i] > vis[a[i][j].v]+a[i][j].w){
                        vis[i] = vis[a[i][j].v] + a[i][j].w;
                        flag = true;
                    }
                }
            }
        }
        cout << vis[n];
        return 0;
    }
    cout << f(1, 0);
    return 0;
}