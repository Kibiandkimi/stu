//
// Created by kibi on 2022/10/28.
//
#include <bits/stdc++.h>
using namespace std;

int raw[100005];

class Tr{
public:
    int l[400005], r[400005], val[400005], ls[400005], rs[400005];
}tr;

void read(int &x);
void build(int u, int l, int r);
int query(int u, int l, int r);

int main(){
    int m, n;
    read(m), read(n);
    for(int i = 1; i <= m; i++){
        read(raw[i]);
    }
    build(1, 1, m);
    for(int i = 1; i <= n; i++){
        static int l, r;
        read(l), read(r);
        printf("%d ", query(1, l, r));
    }
}

int query(int u, int l, int r){
    if(l <= tr.l[u] && tr.r[u] <= r){
        return tr.val[u];
    }
    int ans = 1e9;
    if(l <= tr.r[tr.ls[u]]){
        ans = min(ans, query(tr.ls[u], l, r));
    }
    if(r >= tr.l[tr.rs[u]]){
        ans = min(ans, query(tr.rs[u], l, r));
    }
    return ans;
}

void build(int u, int l, int r){
    tr.l[u] = l, tr.r[u] = r;
    if(l == r){
        tr.val[u] = raw[l];
        return ;
    }
    int mid = (l+r)/2;
    build(tr.ls[u] = u*2, l, mid);
    build(tr.rs[u] = u*2+1, mid+1, r);
    tr.val[u] = min(tr.val[tr.ls[u]], tr.val[tr.rs[u]]);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}