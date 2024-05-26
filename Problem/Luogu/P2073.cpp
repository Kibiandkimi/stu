//
// Created by kibi on 2022/10/29.
//
//
// Created by kibi on 2022/10/28.
//
#include <bits/stdc++.h>
using namespace std;

#define int long long

mt19937 rnd(random_device{}());

class FhqTreap{
    static const int Size = 1000005;
    int siz[Size], ls[Size], rs[Size], val[Size], pri[Size], cnt;
    unsigned int rnk[Size];
    void updSize(int u){
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    }
public:
    int root;
    int addNode(int v, int w){
        cnt++;
        siz[cnt] = 1, val[cnt] = v, pri[cnt] = w, rnk[cnt] = rnd();
        return cnt;
    }
    void split(int &x, int &y, int k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(pri[pos] <= k){
                x = pos;
                split(rs[pos], y, k, rs[pos]);
            }else{
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }
            updSize(pos);
        }
    }
    void splitBySiz(int &x, int &y, int k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(siz[ls[pos]] >= k){
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }else{
                x = pos;
                split(rs[pos], y, k, rs[pos]);
            }
            updSize(pos);
        }
    }
    int merge(int x, int y){
        if(!(x&&y)){
            return x+y;
        }
        if(rnk[x] < rnk[y]){
            rs[x] = merge(rs[x], y);
            updSize(x);
            return x;
        }else{
            ls[y] = merge(x, ls[y]);
            updSize(y);
            return y;
        }
    }
    int delLast(){
        int now = root;
        while(rs[now]){
            now = rs[now];
        }
        static int tem, rootT;
        split(rootT, tem, pri[now]-1, root);
        root = rootT;
        return pri[tem];
    }
    int delFirst(){
        int now = root;
        while(ls[now]){
            now = ls[now];
        }
        static int tem, rootT;
        split(tem, rootT, pri[now], root);
        root = rootT;
        return pri[tem];
    }
    int delRnk(int k){
        static int a, b, c, tem;
        splitBySiz(a, b, k-1, root);
        splitBySiz(tem, c, 1, b);
        root = merge(a, c);
        return pri[b];
    }
    long long totP, totV;
    void queryAll(int u){
        totP += pri[u], totV += val[u];
        if(ls[u]){
            queryAll(ls[u]);
        }
        if(rs[u]){
            queryAll(rs[u]);
        }
    }
};

void read(int &x);

signed main(){
    static FhqTreap tr;
    while(true){
        static int opt, num;
        static bool flag[1000005];
        read(opt);
        if(opt == -1) {
            break;
        }
        if(opt == 1){
            static int v, w;
            read(v), read(w);
            if(!flag[w]) {
                static int a, b;
                tr.split(a, b, w, tr.root);
                tr.root = tr.merge(tr.merge(a, tr.addNode(v, w)), b);
                num++;
                flag[w] = true;
            }
        }else if(opt == 2){
            if(num) {
                flag[tr.delLast()] = false;
                num--;
            }
        }else if(opt == 3){
            if(num) {
                flag[tr.delFirst()] = false;
                num--;
            }
        }
    }
    tr.queryAll(tr.root);
    printf("%lld %lld", tr.totV, tr.totP);
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