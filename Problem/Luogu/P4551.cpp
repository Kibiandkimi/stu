//
// Created by kibi on 2021/10/12.
//
#include <bits/stdc++.h>
using namespace std;
struct node{
    int v,w;
};
struct trie{
    int t[2];
}t[2000005];
vector<node> a[2000005];
int sum[2000005];
int n,tot;
void f(int x, int fa){
    int sa = a[x].size();
    for(int i = 0; i < sa; i++){
        int v = a[x][i].v, w = a[x][i].w;
        if(v != fa){
            sum[v] = sum[x]^w;
            f(v, x);
        }
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v,w});
        a[v].push_back({u,w});
    }
    f(1, -1);
    for(int i = 1; i <= n; i++){
        int x = 0;
        for(int j = (1<<30); j; j>>=1){
            bool c = sum[i]&j;
            if(!t[x].t[c]){
                t[x].t[c] = ++tot;
            }
            x = t[x].t[c];
        }
    }
    int mx = 0;
    for(int i = 1; i <= n; i++){
        int as = 0, x = 0;
        for(int j = (1<<30); j; j>>=1){
            bool c = sum[i]&j;
            if(t[x].t[!c]){
                as += j;
                x = t[x].t[!c];
            }else{
                x = t[x].t[c];
            }
        }
        mx = max(mx, as);
    }
    printf("%d", mx);
}