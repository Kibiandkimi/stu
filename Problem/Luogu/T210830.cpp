#include <bits/stdc++.h>
using namespace std;
struct node{
    int l,r;
    int s;
    int mx;
};
struct edge{
    int sl, sr;
    //    int s;
    int el, er;
};
struct re{
    int l, r, s;
    int x;
};
edge e[3000005];
re oe[3000005];
int num = 1;
int cnt = 1;
int n, a[300005];
int p[300005];
int mx = 0;
node tr[3000005];
void build(int x, int l, int r){
    tr[x].l = l;
    tr[x].r = r;
    tr[x].s = 0;
    tr[x].mx = 0;
    if(l==r){
        return;
    }
    int mid = (l+r)/2;
    build(x*2, l, mid);
    build(x*2+1, mid+1, r);
}
void add(int x, int l, int r, int al, int ar, int d){
    if(r<al||l>ar){
        return;
    }
    if(l==r){
        tr[x].s += d;
        tr[x].mx = tr[x].s;
        return;
    }
    int mid = (l+r)/2;
    //    if(l>=al&&r<=ar){
    //
    //    }else if(l<=al){
    //
    //    }
    add(x*2, l, mid, al, ar, d);
    add(x*2+1, mid+1, r, al, ar, d);
    tr[x].s = tr[x*2].s + tr[x*2+1].s;
    tr[x].mx = max(tr[x*2].mx, tr[x*2+1].mx);
}
bool cmp(re a, re b){
    if(a.x==b.x){
        return a.s < b.s;
    }
    return a.x<b.x;
}
//int query(int)
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    build(1, 1, n);
    //    for(int i = 1; i <= n; i++){
    //        p[i] = 1;
    //    }
    for(int i = 1; i <= n; i++){
        if(p[a[i]]==0){
            e[cnt++] = {1, i, i, n};
            p[a[i]] = cnt;
        }else{
            e[p[a[i]]].er = i-1;
            e[cnt++] = {e[p[a[i]]].sr+1, i, i, n};
        }
    }
    for(int i = 1; i < cnt; i++){
        oe[num++] = {e[i].sr,e[i].er,1,e[i].sl};
        oe[num++] = {e[i].sr,e[i].er,-1,e[i].el+1};
    }
    sort(oe+1, oe+num, cmp);
    for(int i = 1; i < num; i++){
        add(1, 1, n, oe[i].l, oe[i].r, oe[i].s);
        mx = max(mx, tr[1].mx);
    }
    printf("%d", mx);
}