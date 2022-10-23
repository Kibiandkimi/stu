//
// Created by kibi on 2022/10/22.
//
#include <bits/stdc++.h>
using namespace std;
const int Size = 1000005;

class Seg{
    class Node{
    public:
        int l, r, ls, rs, mn, tag;
    }node[Size*3];
    int *raw;
    //    int val[Size*3], l[Size*3], r[Size*3], ls[Size*3], rs[Size*3], mn[Size*3];

    void pushDown(int u){
        static Node *now, *ls, *rs;
        now = &node[u], ls = &node[node[u].ls], rs = &node[node[u].rs];
        if(now->tag){
            ls -> tag += now -> tag;
            rs -> tag += now -> tag;
            ls -> mn -= now -> tag;
            rs -> mn -= now -> tag;
            now -> tag = 0;
        }
    }

    void pushUp(int u){
        node[u].mn = min(node[node[u].ls].mn, node[node[u].rs].mn);
    }

    void build(int u, int l, int r){
        Node &now = node[u];
        now.l = l, now.r = r;
        if(l == r){
            now.mn = raw[l];
            return ;
        }
        now.ls = u*2, now.rs = u*2+1;
        int mid = (l+r)/2;
        build(now.ls, l, mid);
        build(now.rs, mid+1, r);
        pushUp(u);
    }

    bool update(int u, int l, int r, int v){
        Node &now = node[u];
        if(l <= now.l && now.r <= r){
            now.tag += v;
            now.mn -= v;
            return now.mn >= 0;
        }
        pushDown(u);
        Node &ls = node[node[u].ls], &rs = node[node[u].rs];
        if(l <= ls.r){
            update(now.ls, l, r, v);
        }
        if(rs.l <= r){
            update(now.rs, l, r, v);
        }
        pushUp(u);
        return now.mn >= 0;
    }

public:
    Seg(int *rawT, int size){
        raw = rawT;
        build(1, 1, size);
    }

    bool update(int l, int r, int v){
        return update(1, l, r, v);
    }
};

void read(int &x);

int main(){
    static int n, m, raw[1000005];
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        read(raw[i]);
    }
    static Seg seg(raw, n);
    for(int i = 1; i <= m; i++){
        static int v, l, r;
        read(v), read(l), read(r);
        if(!seg.update(l, r, v)){
            printf("-1\n%d", i);
            return 0;
        }
    }
    printf("0");
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