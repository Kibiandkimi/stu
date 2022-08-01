//
// Created by kibi on 2021/8/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,b[5005];
struct node{
    int u,v,w;
};
node a[200005];
int cmp(node a, node b){
    return a.w < b.w;
}
int find(int x){
    if(b[x]!=x)b[x]=find(b[x]);
    return b[x];
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[i] = node({u,v,w});
    }
    sort(a+1,a+1+m,cmp);
    int w = 0;
    for(int i = 1; i <= m; i++){
        if(find(a[i].u)!=find(a[i].v)){
            b[find(a[i].u)] = find(a[i].v);
            w += a[i].w;
        }
    }
    int t = find(1);
    for(int i = 1; i <= n; i++){
        if(find(i) != t){
            cout << "orz";
            return 0;
        }
    }
    cout << w;
    return 0;
}