//
// Created by kibi on 2022/7/17.
//
//0pts~~
#include <bits/stdc++.h>
using namespace std;
int n, k;
vector<int> g[1000005];
int b[1000005];
int num;
vector<int> v[2];
int h[1000005];
int vis[1000005];
int is[1000005];
int top;
int als;
int vd[1000005];
int cnt;
int ii = 2;
int find(int x){
    if(b[x] != x){
        return b[x] = find(b[x]);
    }
    return x;
}

int f(int u, int fa, bool fl = false){
    if(vis[u] == ii){
        top = u;
        //        r[++cnt] = u;
        is[u] = ii;
        return 0;
    }
    int sa = g[u].size();
    int res = 0;
    vis[u] = ii;
    for(int i = 0; i < sa; i++){
        if(g[u][i] == fa){
            continue ;
        }
        if(fl){
            res += f(g[u][i], u, true);
        }else if(top){
            int t1 = f(g[u][i], u, true);
            //            v[0].push_back(t1);
            res += t1;
        }else{
            int tt = f(g[u][i], u);
            if(!top){
                //                t1 = max(tt, t1);
                //                v[0].push_back(tt);
            }
            res += tt;
        }
    }
    if((!fl) && top){
        //        r[++cnt] = u;
        is[u] = ii;
    }
    vd[u] = res+1;
    return res + 1;
}

bool cmp(int a, int b){
    return a > b;
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        int x = find(u), y = find(v);
        if(x < y){
            b[y] = x;
        }else if(x > y){
            b[x] = y;
        }else{
            num++;
        }
    }
    for(int i = 1; i <= n; i++){
        if(!vis[b[i]]){
            h[++cnt] = b[i];
            vis[b[i]] = true;
        }
    }


    sort(h+1, h+num+1);
    for(int i = 1; i <= num; i++){
        memset(vd, 0 ,(als) * sizeof (int));
        cnt = 0;
        top = 0;
        als = f(h[i], 0) - 1;
        if(g[h[i]].size()==1){
            v[0].push_back(als);
        }else if(is[h[i]] == ii){
            int sg = g[h[i]].size();
            int t2 = 0;
            for(int j = 0; j < sg; j++){
                if(is[ g[ h[i] ][j] ] == ii){
                    t2 += vd[ g[ h[i] ][j] ];
                }else{
                    v[0].push_back(vd[ g[ h[i] ][j] ]);
                }
            }
            v[1].push_back(t2);

        }else{
            int sg = g[h[i]].size();
            for(int j = 0; j < sg; j++){
                v[0].push_back(vd[ g[ h[i] ][j] ]);
            }
        }
        ii++;
    }
    sort(v[0].begin(), v[0].end(), cmp);
    sort(v[1].begin(), v[1].end(), cmp);
    int ans = 0;
    int i1 = 0, i2 = 0;
    while(k > 0){
        if(k <= v[0][i1]){
            printf("%d", ans+1);
            return 0;
        }
        if(2*v[0][i1] > v[1][i2]){
            ans++;
            k -= v[0][i1];
            i1++;
        }else{
            ans += 2;
            k -= v[1][i2];
            i2++;
        }
    }
    printf("%d", ans);
}