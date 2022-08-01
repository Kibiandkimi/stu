//
// Created by kibi on 2022/6/26.
//
//主席树
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int l, r, ls, rs, sum;
}node[30000100];
int n, m, cnt, a[30000100], rt, root[30000100];

//void cl(int o){
//    cnt++;
//    node[cnt] = node[o];
//}

void build(int l, int r, int u){
    if(l == r){
        node[u].sum = a[l];
        node[u].l = node[u].r = l;
        return ;
    }
    int mid = (l+r)/2;
    node[u].ls = cnt++;
    node[u].rs = cnt++;
    build(l, mid, node[u].ls);
    build(mid+1, r, node[u].rs);
    node[u].l = node[node[u].ls].l;
    node[u].r = node[node[u].rs].r;
    //    node[u].sum = node[node[u].ls].sum + node[node[u].rs].sum;
}

void update(int u, int x, int v){
    //    cl(u);
    node[cnt] = node[u];
    u = cnt;
    if(node[u].l == node[u].r){
        node[u].sum = v;
        return ;
    }
    int mid = (node[u].l + node[u].r)/2;
    if(x <= mid){
        int ls = node[u].ls;
        node[u].ls = ++cnt;
        update(ls, x, v);
    }else{
        int rs = node[u].rs;
        node[u].rs = ++cnt;
        update(rs, x, v);
    }
}

int query(int u, int x){
    if(node[u].l == node[u].r){
        return node[u].sum;
    }
    int mid = (node[u].l + node[u].r)/2;
    if(x <= mid){
        return query(node[u].ls, x);
    }
    return query(node[u].rs, x);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    cnt = 0;
    rt = cnt++;
    root[0] = rt;
    build(1, n, rt);
    int i = 0;
    while(m--){
        i++;
        int ver, op, x, val;
        scanf("%d %d %d", &ver, &op, &x);
        if(op == 1){
            scanf("%d", &val);
            root[i] = ++cnt;
            update(root[ver], x, val);
        }else if(op == 2){
            printf("%d\n", query(root[ver], x));
            root[i] = root[ver];
        }
    }
}
