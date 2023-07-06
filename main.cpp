#include <bits/stdc++.h>
using namespace std;

const int N = 50000, M = 50000;

void read(int &x);

class SeTree{
    int val[N*4+5], ls[N*4+5], rs[N*4+5], l[N*4+5], r[N*4+5], valL[N*4+5], valR[N*4+5];
    bool flag_in[N*4+5], flag_out[N*4+5];

    void update(int u) {
        val[u] = max(max(val[ls[u]], val[rs[u]]), valR[ls[u]] + valL[rs[u]]);
        valL[u] = valL[ls[u]] == val[ls[u]] ? val[ls[u]] + valL[rs[u]] : valL[ls[u]];
        valR[u] = valR[rs[u]] == val[rs[u]] ? val[rs[u]] + valR[ls[u]] : valR[rs[u]];
    }

    void build(int _l, int _r, int u){
        l[u] = _l, r[u] = _r, flag_in[u] = flag_out[u] = false;
        if(_l == _r){
            val[u] = valL[u] = valR[u] = 1;
            return;
        }
        int mid = (_l + _r) / 2;
        ls[u] = u*2, rs[u] = u*2+1;
        build(_l, mid, ls[u]);
        build(mid + 1, _r, rs[u]);
        update(u);
    }

    void push_down(int u){
        if(flag_in[u]){
            flag_in[u] = false;
            flag_in[ls[u]] = flag_in[rs[u]] = true;
            flag_out[ls[u]] = flag_out[rs[u]] = false;
            val[ls[u]] = val[rs[u]] = valL[ls[u]] = valL[rs[u]] = valR[ls[u]] = valR[rs[u]] = 0;
        }
        if(flag_out[u]){
            flag_out[u] = false;
            flag_out[ls[u]] = flag_out[rs[u]] = true;
            flag_in[ls[u]] = flag_in[rs[u]] = false;
            val[ls[u]] = valL[ls[u]] = valR[ls[u]] = r[ls[u]] - l[ls[u]] + 1;
            val[rs[u]] = valL[rs[u]] = valR[rs[u]] = r[rs[u]] - l[rs[u]] + 1;
        }
    }

    int query(int u, int x){
        if(val[u] < x){
            return 0;
        }
        push_down(u);
        int t = query(ls[u], x);
        if(t){
            return t;
        }
        if(valR[ls[u]] && valR[ls[u]] + valL[rs[u]] >= x){
            return r[ls[u]] - valR[ls[u]] + 1;
        }
        t = query(rs[u], x);
        return t;
    }

public:
    SeTree(int size){
        build(1, size, 1);
    }

    void check_in(int _l, int _r, int u = 1){
        if(_l <= l[u] && r[u] <= _r){
            flag_in[u] = true;
            flag_out[u] = false;
            val[u] = valL[u] = valR[u] = 0;
            return ;
        }
        push_down(u);
        if(_l <= r[ls[u]]){
            check_in(_l, _r, ls[u]);
        }
        if(_r >= l[rs[u]]){
            check_in(_l, _r, rs[u]);
        }
        update(u);
    }

    void check_out(int _l, int _r, int u = 1){
        if(_l <= l[u] && r[u] <= _r){
            flag_out[u] = true;
            flag_in[u] = false;
            val[u] = valL[u] = valR[u] = r[u] - l[u] + 1;
            return ;
        }
        push_down(u);
        if(_l <= r[ls[u]]){
            check_out(_l ,_r, ls[u]);
        }
        if(_r >= l[rs[u]]){
            check_out(_l, _r, rs[u]);
        }
        update(u);
    }

    int query(int x){
        return query(1, x);
    }
};

int main(){
    int n, m;
    read(n), read(m);

    static SeTree tree(n);

    while(m--){
        int opt;
        read(opt);
        if(opt == 1){
            int x;
            read(x);
            int l = tree.query(x);
            if(l){
                printf("%d\n", l);
                tree.check_in(l, l+x-1);
            }else{
                printf("0\n");
            }
        }else if(opt == 2){
            int x, y;
            read(x), read(y);
            tree.check_out(x, x+y-1);
        }
    }

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