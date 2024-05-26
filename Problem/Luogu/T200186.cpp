//
// Created by kibi on 2021/9/12.
//
#include <bits/stdc++.h>
using namespace std;
// int n,m,c[505],e[505],dfn[505],low[505],num;
int n,m,c[505],d[505],p,vis[505],bb[505][505],tis[505],ris[505],vvis[505];
vector<int> a[505],b[505];
void f(int x, int num){
    if(vis[x]){
        return;
    }
    if(!d[num]){
        d[num] = c[x];
    }
    vis[x] = num;
    int sa = a[x].size();
    vector<int> t;
    for(int i = 0; i < sa; i++){
        if(c[a[x][i]]==c[x]){
            // d[find(a[x][i])] = d[find(x)];
            f(a[x][i], num);
        }else{
            t.push_back(a[x][i]);
        }
    }
    int st = t.size();
    for(int i = 0; i < st; i++){
        if(vis[t[i]]){
            if(!bb[vis[t[i]]][num]){
                b[vis[t[i]]].push_back(num);
                b[num].push_back(vis[t[i]]);
                bb[num][vis[t[i]]] = bb[vis[t[i]]][num] = 1;
            }
        }else{
            f(t[i], ++p);
            if(!bb[vis[t[i]]][num]){
                b[vis[t[i]]].push_back(num);
                b[num].push_back(vis[t[i]]);
                bb[num][vis[t[i]]] = bb[vis[t[i]]][num] = 1;
            }
        }
    }
}
int ff(int x){
    if(vvis[x]){
        return 0;
    }
    int s = 0;
    vvis[x] = 1;
    int sb = b[x].size();
    for(int i = 0; i < sb; i++){
        if(d[x]!=d[b[x][i]]){
            if(!tis[b[x][i]]){
                s++;
                tis[b[x][i]] = 1;
            }
        }else{
            s += ff(b[x][i]);
        }
    }
    return s;
}
void r(int x){
    if(ris[x])return;
    if(d[x]==1){
        d[x] = 2;
    }else{
        d[x] = 1;
    }
    int sb = b[x].size();
    for(int i = 0; i < sb; i++){
        if(d[x]!=d[b[x][i]]){
            r(b[x][i]);
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &c[i]);
        c[i]++;
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    f(1, ++p);
    int s = 0,mx = 0,mxp;
    while(true){
        memset(vvis, 0, sizeof(vvis));
        for(int i = 1; i <= p; i++){
            if(vvis[i]){
                continue;
            }
            memset(tis, 0, sizeof(tis));
            int t = ff(i);
            if(t > mx){
                mxp = i;
                mx = t;
            }
        }
        if(!mx){
            break;
        }
        memset(ris, 0, sizeof(ris));
        r(mxp);
        s++;
        mx=0;
    }
    cout << s;
}