#include <bits/stdc++.h>
using namespace std;
int n, v, a[2000005], mx[2000005], b[2000005], p;
long long s[2000005];
struct node{
    int l, r, ls, rs, id;
    long long v;
}tr[4000005];

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
//        mx[i] = max(mx[i-1], a[i]);
    }
    build(1, 1, n);
//    int T;
//    read(T);
    long long finalAns1 = 0, finalAns2 = 0;
    while(T--){
        int x, k;
        read(x), read(k);
        if(n-x+1<k){
            continue;
        }
        int ans;
        int rans = mx[x-1];
//        change(1, x, ans+(n-x+1)*v);
        ans = query(1, x+1, x+k-1);
//        change(1, x, r);
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
    if(tr[tr[u].ls].v>tr[tr[u].rs].v){
        tr[u].v = tr[tr[u].ls].v;
        tr[u].id = tr[tr[u].ls].id;
    }else{
        tr[u].v = tr[tr[u].rs].v;
        tr[u].id = tr[tr[u].rs].id;
    }
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    if(l == r){
        tr[u].id = l;
        tr[u].v = s[l];
        return;
    }
    tr[u].ls = u*2;
    tr[u].rs = u*2+1;
    int mid = (l+r)/2;
    build(tr[u].ls, l, mid);
    build(tr[u].rs, mid+1, r);
    upd(u);
//    tr[u].v = max(tr[tr[u].ls].v, tr[tr[u].rs].v);
}

int query(int u, int l, int r){
    if(l<=tr[u].l&&tr[u].r<=r){
        return tr[u].id;
    }
    int t1 = 0, t2 = 0;
    if(l<=tr[tr[u].ls].r){
        t1 = query(tr[u].ls, l, r);
    }
    if(r>=tr[tr[u].rs].l){
        t2 = query(tr[u].rs, l, r);
    }
    if(!t1){
        return t2;
    }
    if(!t2){
        return t1;
    }
    return s[t1]>s[t2]?t1:t2;
}

//void change(int u, int x, long long v){
//    if(tr[u].l == tr[u].r){
//        tr[u].v = v;
//        return;
//    }
//    if(x<=tr[tr[u].ls].r){
//        change(tr[u].ls, x, v);
//    }else{
//        change(tr[u].rs, x, v);
//    }
//    upd(u);
//}