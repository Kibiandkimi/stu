//
// Created by kibi on 2021/10/17.
//
#include <bits/stdc++.h>
using namespace std;
int n;
// int l[5005], w[5005];
struct node{
    int l, w;
}a[5005];
bool cmp(node a, node b){
    return (a.l==b.l)?(a.w>b.w):(a.l>b.l);
}
int d[5005];
int s[5005];
int len = 1;
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &a[i].l, &a[i].w);
    }
    sort(a+1, a+1+n, cmp);
    d[1] = a[1].w;
    for(int i = 1; i <= n; i++){
        if(d[len]<a[i].w){
            d[++len] = a[i].w;
        }else{
            int p = lower_bound(d+1, d+1+len, a[i].w) - d;
            d[p] = a[i].w;
        }
    }
    cout << len;
}