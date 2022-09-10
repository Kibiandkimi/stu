//
// Created by kibi on 2022/9/10.
//
#include <bits/stdc++.h>
using namespace std;
int n, v, a[2000005], p;
int mx[2000005], b[2000005];
int s[2000005];
struct node{
    int l, r, id;
}tr[6000005];

void read(int &x);
void build(int u, int l, int r);
int query(int u, int l, int r);
//void change(int u, int x, long long v);

int main(){
    int T;
    read(n), read(T), read(v);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        s[i] = a[i]+v*(n-i+1);
        if(a[i]>mx[i-1]){
            mx[i] = b[i] = a[i]+v;
            p = i;
        }else if(a[i]==b[p]){
            mx[i] = b[i] = a[i]+v;
            p = i;
        }else{
            mx[i] = b[p] = b[p]+v;
        }
    }
    build(1, 1, n);
    long long finalAns1 = 0, finalAns2 = 0;
    while(T--){
        int x, k;
        read(x), read(k);
        if(n-x+1<k){
            continue;
        }
        int ans;
        int rans = mx[x-1];
        ans = query(1, x+1, x+k-1);
        if(ans){
            ans = a[ans] + 1 - (ans-x)*v;
        }
        ans = max(ans, rans);
        finalAns1 ^= ans;
        finalAns2 += ans;
    }
    printf("%lld %lld", finalAns1, finalAns2);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void upd(int u){
    if(s[tr[u*2].id]>s[tr[u*2+1].id]){
        tr[u].id = tr[u*2].id;
    }else{
        tr[u].id = tr[u*2+1].id;
    }
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    if(l == r){
        tr[u].id = l;
        return;
    }
    int mid = (l+r)/2;
    build(u*2, l, mid);
    build(u*2+1, mid+1, r);
    upd(u);
}

int query(int u, int l, int r){
    if(l<=tr[u].l&&tr[u].r<=r){
        return tr[u].id;
    }
    int t1 = 0, t2 = 0;
    if(l<=tr[u*2].r){
        t1 = query(u*2, l, r);
    }
    if(r>=tr[u*2+1].l){
        t2 = query(u*2+1, l, r);
    }
    if(!t1){
        return t2;
    }
    if(!t2){
        return t1;
    }
    return s[t1]>s[t2]?t1:t2;
}