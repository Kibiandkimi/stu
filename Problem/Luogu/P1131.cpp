//
// Created by kibi on 2021/10/1.
//
#include <bits/stdc++.h>
using namespace std;
struct node{
    long long s,t;
};
long long n,root;
vector<node> v[500005];
long long ans;
long long mx[500005];

bool f(int x, int fa){
    int sa = v[x].size();
    for(int i = 0; i < sa; i++){
        (v[x][i].s==fa)||f(v[x][i].s, x);
    }
    for(int i = 0; i < sa; i++){
        (v[x][i].s==fa)||(mx[x] = max(mx[x], mx[v[x][i].s]+v[x][i].t));
    }
    for(int i = 0; i < sa; i++){
        (v[x][i].s==fa)||(ans += (mx[x]-(mx[v[x][i].s]+v[x][i].t)));
    }
    sa = v[fa].size();
    // for(int i = 0; i < sa; i++){
    //     v[fa][i].s==x&&
    // }
    return 0;
}

int main(){
    cin >> n >> root;
    for(long long i = 1; i < n; i++){
        long long a,b,t;
        scanf("%lld %lld %lld", &a, &b, &t);
        v[a].push_back(node({b,t}));
        v[b].push_back(node({a,t}));
    }
    f(root,0);
    // cout << ans;
    printf("%lld", ans);
    return 0;
}