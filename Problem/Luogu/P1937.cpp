//
// Created by kibi on 23-7-3.
//
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 100000;
void read(int &x);
class SeTree{
    int val[N*8+5], ls[N*8+5], rs[N*8+5], l[N*8+5], r[N*8+5], flag[N*8+5];

    void push_down(int u){
        if(flag[u] != 0){
            flag[ls[u]] += flag[u], flag[rs[u]] += flag[u];
            val[ls[u]] += flag[u], val[rs[u]] += flag[u];
            flag[u] = 0;
        }
    }

    void build(int u, int _l, int _r, const int* arr){
        l[u] = _l, r[u] = _r, flag[u] = 0;
        if(_l == _r){
            val[u] = arr[_l];
            return;
        }
        ls[u] = u*2, rs[u] = u*2+1;
        build(ls[u], _l, (_l+_r)/2, arr);
        build(rs[u], (_l+_r)/2 + 1, _r, arr);
        val[u] = min(val[ls[u]], val[rs[u]]);
    }

public:
    SeTree(int size, const int* arr){
        build(1, 1, size, arr);
    }

    void add(int _l, int _r, int v, int u = 1) {
        if(_l <= l[u] && r[u] <= _r){
            flag[u] += v;
            val[u] += v;
            return;
        }
        push_down(u);
        if(_l <= r[ls[u]]){
            add(_l, _r, v, ls[u]);
        }
        if(l[rs[u]] <= _r){
            add(_l, _r, v, rs[u]);
        }
        val[u] = min(val[ls[u]], val[rs[u]]);
    }

    int query(int _l, int _r, int u = 1){
        if(_l <= l[u] && r[u] <= _r){
            return val[u];
        }
        int res = 1e9;
        push_down(u);
        if(_l <= r[ls[u]]){
            res = query(_l, _r, ls[u]);
        }
        if(l[rs[u]] <= _r){
            res = min(res, query(_l, _r, rs[u]));
        }
        return res;
    }
};
class q{
public:
    int l, r;
    static bool cmp(q a, q b){
        if(a.r != b.r){
            return a.r < b.r;
        }
        return a.l > b.l;
    }
};

int main(){
    int n, m;
    static q _q[M+5];
    read(n), read(m);
    int c[N+5] = {0};
    for(int i = 1; i <= n; i++){
        read(c[i]);
    }
    static SeTree tree(n, c);
    for(int i = 1; i <= m; i++){
        read(_q[i].l), read(_q[i].r);
    }
    sort(_q+1, _q+1+m, q::cmp);

    int ans = 0;
    for(int i = 1; i <= m; i++){
        int res = tree.query(_q[i].l, _q[i].r);
        if(res > 0){
            ans++;
            tree.add(_q[i].l, _q[i].r, -1);
        }
    }

    printf("%d", ans);

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