//
// Created by kibi on 2021/8/11.
//
#include <bits/stdc++.h>
using namespace std;
int a[1000005],n,r[1000005][2];
int find(int x){
    if((a[x])!=x){
        a[x] = find(a[x]);
    }
    return a[x];
}
int f(){
    //    memset(a, 0, sizeof a);
    for(int i = 1; i <= 1000001; i++){
        a[i] = i;
    }
    //    memset(r, 0, sizeof r);
    int t1 = 1, t2 = 1;
    map<int, int> m;
    cin >> n;
    for(int i = 1; i <= n; i++){
        int u,v,e;
        scanf("%d %d %d", &u, &v, &e);
        if(e) {
            if(!m[u]){
                m[u] = t1++;
            }
            if(!m[v]){
                m[v] = t1++;
            }
            u = m[u];
            v = m[v];
            a[find(v)] = find(u);
        }else{
            if(!m[u]){
                m[u] = t1++;
            }
            if(!m[v]){
                m[v] = t1++;
            }
            u = m[u];
            v = m[v];
            r[t2++][0] = u;
            r[t2-1][1] = v;
        }
    }
    //    bool flag = true;
    for(int i = 1; i < t2; i++){
        int u,v;
        u = find(r[i][0]);
        v = find(r[i][1]);
        if(u==v){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
int t;
int main(){
    cin >> t;
    for(int i = 1; i <= t; i++){
        f();
    }
}