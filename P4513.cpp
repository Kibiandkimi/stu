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

// 2023/8/1
/*

#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

void read(int&);

int main(){
    class SegTree{
        int l[4 * N + 5]{}, r[4 * N + 5]{}, ls[4 * N + 5]{}, rs[4 * N + 5]{}, lmx[4 * N + 5]{}, rmx[4 * N + 5]{}, mx[4 * N + 5]{}, sum[4 * N + 5]{};

        void update(int u){
            sum[u] = sum[ls[u]] + sum[rs[u]];
            mx[u] = max(max(mx[ls[u]], mx[rs[u]]), lmx[rs[u]] + rmx[ls[u]]);
            lmx[u] = max(lmx[ls[u]] , sum[ls[u]] + lmx[rs[u]]);
            rmx[u] = max(rmx[rs[u]] , sum[rs[u]] + rmx[ls[u]]);
        }

        void build(int u, int _l, int _r, const int *data){
            l[u] = _l, r[u] = _r;
            if(_l == _r){
                sum[u] = lmx[u] = rmx[u] = mx[u] = data[_l];
                return;
            }
            int mid = (_l + _r) / 2;
            ls[u] = u*2, rs[u] = u*2+1;
            build(ls[u], _l, mid, data);
            build(rs[u], mid+1, _r, data);

            update(u);
        }

        tuple<int, int, int, int> query(int _l, int _r, int u){ // lmx, rmx, mx, sum
            if(_l <= l[u] && r[u] <= _r){
                return {lmx[u], rmx[u], mx[u], sum[u]};
            }
            int res = -1e9, l_lmx = -1e9, l_rmx = -1e9, r_lmx = -1e9, r_rmx = -1e9, l_sum = 0, r_sum = 0;
            if(_l <= r[ls[u]]){
                auto [lmx, rmx, mx, sum] = query(_l, _r, ls[u]);
                l_lmx = lmx,
                l_rmx = rmx,
                l_sum = sum,
                res = max(res, mx);
            }
            if(_r >= l[rs[u]]){
                auto [lmx, rmx, mx, sum] = query(_l, _r, rs[u]);
                r_lmx = lmx,
                r_rmx = rmx,
                r_sum = sum,
                res = max(res, mx);
            }
            // int l_ = max(_l, l[u]), r_ = min(_r, r[u]);
            int sum = l_sum + r_sum,
                lmx = max(l_lmx , l_sum + r_lmx),
                rmx = max(r_rmx , r_sum + l_rmx);
            res = max(res, l_rmx + r_lmx);
            return {lmx, rmx, res, sum};
        }

    public:

        SegTree(int n, const int *data){
            build(1, 1, n, data);
        }

        int query(int _l, int _r){
            auto [ignore1, ignore2, res, ignore3] = query(_l, _r, 1);
            return res;
        }

        void change(int p, int s, int u = 1){
            if(l[u] == r[u]){
                sum[u] = lmx[u] = rmx[u] = mx[u] = s;
                return;
            }
            if(p <= r[ls[u]]){
                change(p, s, ls[u]);
            }else{
                change(p, s, rs[u]);
            }

            update(u);

        }

    };

    int n, m;

    read(n), read(m);

    static int raw[N + 5];

    for(int i = 1; i <= n; i++){
        read(raw[i]);
    }

    static SegTree tree(n, raw);

    for(int i = 1; i <= m; i++){
        int opt, x, y;
        read(opt), read(x), read(y);
        if(opt == 1){
            if(x > y){
                swap(x, y);
            }
            printf("%d\n", tree.query(x, y));
        }else{
            tree.change(x, y);
        }
    }

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
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

*/