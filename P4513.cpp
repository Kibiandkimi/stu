//
// Created by kibi on 2021/8/24.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[500005];
struct node{
    int l,r,s,ls,rs,ss;
    void init(int l, int r, int s, int ls, int rs, int ss) {
        this->l = l;
        this->r = r;
        this->s = s;
        this->ls = ls;
        this->rs = rs;
        this->ss = ss;
    }
    void ch(int s, int ls, int rs, int ss){
        this->s = s;
        this->ls = ls;
        this->rs = rs;
        this->ss = ss;
    }
    void chs(int s){
        this->s = s;
        this->ls = s;
        this->rs = s;
        this->ss = s;
    }
    int mid(){return (this->l+this->r)/2;}
    bool pd(){return this->l == this->r;}
}tr[2000005];
void build(int l, int r, int x){
    if(l==r){
        tr[x].init(l, r, a[l], a[l], a[l], a[l]);
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, x*2);
    build(mid+1, r, x*2+1);
    int ls, rs, ss;
    ls = max(tr[x*2].s+tr[x*2+1].ls, tr[x*2].ls);
    rs = max(tr[x*2].rs+tr[x*2+1].s, tr[x*2+1].rs);
    ss = max(max(tr[x*2].ss, tr[x*2+1].ss),tr[x*2].rs+tr[x*2+1].ls);
    tr[x].init(l, r, tr[x * 2].s + tr[x * 2 + 1].s, ls, rs, ss);
}
void change(int x, int d, int s){
    if(tr[x].pd()){
        tr[x].chs(s);
        return;
    }
    int mid = tr[x].mid();
    if(d<=mid){
        change(x*2, d, s);
    }else{
        change(x*2+1, d, s);
    }
    int ls, rs, ss, ts;
    ts = tr[x*2].s+tr[x*2+1].s;
    ls = max(tr[x*2].s+tr[x*2+1].ls, tr[x*2].ls);
    rs = max(tr[x*2].rs+tr[x*2+1].s, tr[x*2+1].rs);
    ss = max(max(tr[x*2].ss, tr[x*2+1].ss),tr[x*2].rs+tr[x*2+1].ls);
    tr[x].ch(ts, ls, rs, ss);
}
node query(int l, int r, int x){
    if(l<=tr[x].l&&tr[x].r<=r){
        return tr[x];
    }
    int mid = tr[x].mid();
    if(l > mid)return query(l,r,x*2+1);
    if(r <= mid)return query(l, r, x*2);

    node a = query(l, r, x*2), b = query(l, r, x*2+1), t;
    int s,ls,rs,ss;
    s = a.s+b.s;
    ls = max(a.s + b.ls, a.ls);
    rs = max(a.rs + b.s, b.rs);
    ss = max(max(a.ss, b.ss), a.rs+b.ls);
    t.ch(s, ls, rs, ss);
    return t;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
    build(1, n, 1);
    while(m--){
        int fl;
        scanf("%d", &fl);
        if(fl == 1){
            int a,b;
            scanf("%d %d", &a, &b);
            int l = min(a,b),r = max(a,b);
            int s = query(l, r, 1).ss;
            printf("%d\n", s);
        }else{
            int a,b;
            scanf("%d %d", &a, &b);
            change(1, a, b);
        }
    }
}