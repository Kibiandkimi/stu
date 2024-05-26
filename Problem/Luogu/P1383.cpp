//
// Created by kibi on 22-8-12.
//
#include <bits/stdc++.h>
using namespace std;
int n, cnt = 1;
//char c[100005];
struct node{
    int l, r, ls, rs, v, fa;
}tr[1600005];
vector<int> rt, no;

int new_node(int l, int r, int v, int fa, int ls, int rs){
    tr[++cnt].l = l;
    tr[cnt].r = r;
    tr[cnt].v = v;
    tr[cnt].fa = fa;
    tr[cnt].ls = ls;
    tr[cnt].rs = rs;
    return cnt;
}

void build(int l, int r, int u){
    tr[u].l = l, tr[u].r = r, tr[u].v = 0;
    if(l == r){
        return ;
    }
    int mid = (l+r)/2;
    tr[u].ls = ++cnt;
    tr[u].rs = ++cnt;
    build(l, mid, tr[u].ls);
    build(mid+1, r, tr[u].rs);
    tr[tr[u].ls].fa = tr[tr[u].rs].fa = u;
}

int query(int x, int u){
    if(tr[u].l == tr[u].r){
        return tr[u].v;
    }
    if(x <= tr[tr[u].ls].r){
        return query(x, tr[u].ls);
    }else{
        return query(x, tr[u].rs);
    }
}

void change(int x, int c, int u){
    if(tr[u].l == tr[u].r){
        return ;
    }
//    int mid = (tr[u].l + tr[u].r)/2;
    if(tr[tr[u].ls].r >= x){
        tr[u].ls = new_node(tr[tr[u].ls].l, tr[tr[u].ls].r, c, u, tr[tr[u].ls].ls, tr[tr[u].ls].rs);
        change(x, c, tr[u].ls);
    }else{
        tr[u].rs = new_node(tr[tr[u].rs].l, tr[tr[u].rs].r, c, u, tr[tr[u].rs].ls, tr[tr[u].rs].rs);
        change(x, c, tr[u].rs);
    }
}

int main(){
    scanf("%d", &n);
    int now = 0, root = 1;
    rt.push_back(1);
    no.push_back(0);
//    for(int i = 1; i <= n; i++){
//        char opt[5];
//        scanf("%s", opt);
//        if(opt[0] == 'T'){
//            char x[5];
//            scanf("%s", x);
//            c[++now] = x[0];
//        }else if(opt[0] == 'U'){
//            int x;
//            scanf("%d", &x);
//            now -= x;
//        }else{
//            int x;
//            scanf("%d", &x);
//            printf("%c\n", (char)c[x]);
//        }
//    }
    build(1, n, root);
    for(int i = 1; i <= n; i++){
        char opt[5];
        scanf("%s", opt);
        if(opt[0] == 'T'){
            char c[5];
            scanf("%s", c);
            rt.push_back(new_node(tr[root].l, tr[root].r, 0, 0, tr[root].ls, tr[root].rs));
            root = rt[rt.size()-1];
            no.push_back(now+1);
            change(++now, (int)c[0], root);
        }else if(opt[0] == 'U'){
            int x;
            scanf("%d", &x);
            rt.push_back(rt[rt.size()-1-x]);
            root = rt[rt.size()-1];
            no.push_back(no[no.size()-1-x]);
            now = no[no.size()-1];
        }else{
            int x;
            scanf("%d", &x);
            printf("%c\n", query(x, root));
        }
    }

}