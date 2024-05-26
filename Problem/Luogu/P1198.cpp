//
// Created by kibi on 2022/8/4.
//
//50pts上，100pts下（区别好好看）

//#include <bits/stdc++.h>
//using namespace std;
//int n, t, mod;
//struct node{
//    int ls, rs, v, l, r;
//    void up(int nv){
//        v = max(v, nv);
//    }
//}tr[800005];
//
//void build(int u, int l, int r){
//    tr[u].l = l, tr[u].r = r, tr[u].v = 0;
//    if(l == r){
//        return;
//    }
//    int mid = (l+r)/2;
//    tr[u].ls = u*2, tr[u].rs = u*2+1;
//    build(u*2, l, mid);
//    build(u*2+1, mid+1, r);
//}
//
//void update(int u, int x, int v){
//    tr[u].up(v);
//    if(tr[u].l==tr[u].r){
//        return;
//    }
//    if(tr[tr[u].ls].r>=x){
//        update(tr[u].ls, x, v);
//    }else{
//        update(tr[u].rs, x, v);
//    }
//}
//
//int query(int u, int l, int r){
//    if(tr[u].l>=l&&tr[u].r<=r){
//        return tr[u].v;
//    }
//    int res = 0;
//    if(l<=tr[tr[u].ls].r){
//        res = max(res, query(tr[u].ls, l, r));
//    }
//    if(r>=tr[tr[u].rs].l){
//        res = max(res, query(tr[u].rs, l, r));
//    }
//    return res;
//}
//
//int main(){
//    scanf("%d %d", &n, &mod);
//    build(1, 1, n);
//    int len = 0;
//    int i;
//    for(i = 1; i <= n; i++){
//        char op;
//        scanf("%s", &op);
//        if(op == 'Q'){
//            int l;
//            scanf("%d", &l);
//            t = query(1, len-l+1, len);
//            printf("%d\n", t);
//        }else{
//            int x;
//            scanf("%d", &x);
//            update(1, ++len, (x+t)%mod);
//        }
//    }
//}

#include <bits/stdc++.h>
using namespace std;
int n, t, mod;
struct node{
    int ls, rs, v, l, r;
    void up(int nv){
        v = max(v, nv);
    }
}tr[800005];

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r, tr[u].v = 0;
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    tr[u].ls = u*2, tr[u].rs = u*2+1;
    build(u*2, l, mid);
    build(u*2+1, mid+1, r);
}

void update(int u, int x, int v){
    tr[u].up(v);
    if(tr[u].l==tr[u].r){
        return;
    }
    if(tr[tr[u].ls].r>=x){
        update(tr[u].ls, x, v);
    }else{
        update(tr[u].rs, x, v);
    }
}

int query(int u, int l, int r){
    if(tr[u].l>=l&&tr[u].r<=r){
        return tr[u].v;
    }
    int res = 0;
    if(l<=tr[tr[u].ls].r){
        res = max(res, query(tr[u].ls, l, r));
    }
    if(r>=tr[tr[u].rs].l){
        res = max(res, query(tr[u].rs, l, r));
    }
    return res;
}

int main(){
    scanf("%d %d", &n, &mod);
    build(1, 1, n);
    int len = 0;
    int i;
    for(i = 1; i <= n; i++){
        char op[2];
        scanf("%s", op);
        if(op[0] == 'Q'){
            int l;
            scanf("%d", &l);
            t = query(1, len-l+1, len);
            printf("%d\n", t);
        }else{
            int x;
            scanf("%d", &x);
            update(1, ++len, (x+t)%mod);
        }
    }
}