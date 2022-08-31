//
// Created by kibi on 22-8-31.
//
//TODO *
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
struct Tree{
    int ls, rs, s;
}tr[MAXN*400];
struct Opt{
    bool b;
    int l, r, k, pos, t;
}q[MAXN];
int n, m, a[MAXN], o[MAXN*2], rt[MAXN], len, tot, tem1[20], tem2[20], cnt1, cnt2;

int getType(int c);
void read(int &x);
void preModify(int x, int v);
void modify(int &u, int l, int r, int pos, int v);
int preQuery(int l, int r, int k);
int query(int l, int r, int k);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        o[++len] = a[i];
    }
    for(int i = 1; i <= m; i++){
        int opt;
        read(opt);
        q[i].b = (opt=='Q');
        if(q[i].b){
            read(q[i].l), read(q[i].r), read(q[i].k);
        }else{
            read(q[i].pos), read(q[i].t);
            o[++len] = q[i].t;
        }
    }
    sort(o+1, o+len+1);
    len = unique(o+1, o+len+1)-o-1;
    for(int i = 1; i <= n; i++){
        preModify(i, 1);
    }
    for(int i = 1; i <= m; i++){
        if(q[i].b){
            printf("%d\n", o[preQuery(q[i].l, q[i].r, q[i].k)]);
        }else{
            preModify(q[i].pos, -1);
            a[q[i].pos] = q[i].t;
            preModify(q[i].pos, 1);
        }
    }
    return 0;
}

int getType(int c){
    return ('0'<=c&&c<='9')?1:(c=='Q'||c=='C'?2:0);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(!getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    if(getType(c) == 2){
        x = c;
        return ;
    }
    while(getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void preModify(int x, int v){
    int k = lower_bound(o+1, o+len+1, a[x]) - o;
    for(int i = x; i <= n; i+=(i&-i)){
        modify(rt[i], 1, len, k, v);
    }
}

void modify(int &u, int l, int r, int pos, int v){
    if(!u){
        u = ++tot;
    }
    tr[u].s += v;
    if(l == r){
        return ;
    }
    int mid = (l+r)/2;
    if(pos <= mid){
        modify(tr[u].ls, l, mid, pos, v);
    }else{
        modify(tr[u].rs, mid+1, r, pos, v);
    }
}

int preQuery(int l, int r, int k){
    memset(tem1, 0, sizeof tem1);
    memset(tem2, 0, sizeof tem2);
    cnt1 = cnt2 = 0;
    for(int i = r; i; i -= (i&-i)){
        tem2[++cnt2] = rt[i];
    }
    for(int i = l-1; i; i -= (i&-i)){
        tem1[++cnt1] = rt[i];
    }
    return query(1, len, k);
}

int query(int l, int r, int k) {
    if(l == r){
        return l;
    }
    int mid = (l+r)/2, sum = 0;
    for(int i = 1; i <= cnt2; i++){
        sum += tr[tr[tem2[i]].ls].s;
    }
    for(int i = 1; i <= cnt1; i++){
        sum -= tr[tr[tem1[i]].ls].s;
    }
    if(k <= sum){
        for(int i = 1; i <= cnt2; i++){
            tem2[i] = tr[tem2[i]].ls;
        }
        for(int i = 1; i <= cnt1; i++){
            tem1[i] = tr[tem1[i]].ls;
        }
        return query(l, mid, k);
    }else{
        for(int i = 1; i <= cnt2; i++){
            tem2[i] = tr[tem2[i]].rs;
        }
        for(int i = 1; i <= cnt1; i++){
            tem1[i] = tr[tem1[i]].rs;
        }
        return query(mid+1, r, k-sum);
    }
}
