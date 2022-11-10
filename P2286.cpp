//
// Created by kibi on 2022/10/29.
//
//
// Created by kibi on 2022/10/28.
//
#include <bits/stdc++.h>
using namespace std;

//#define int long long

mt19937 rnd(random_device{}());

class FhqTreap {
    static const int Size = 80005;
    int siz[Size], ls[Size], rs[Size], cnt;
    long long val[Size], rnk[Size];
    void updSiz(int u){
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    }
public:
    int root;
    int newNode(long long x){
        ++cnt;
        siz[cnt] = 1, val[cnt] = x, rnk[cnt] = rnd();
        return cnt;
    }
    void split(int &x, int &y, long long k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(val[pos] <= k){
                x = pos;
                split(rs[pos], y, k, rs[pos]);
            }else{
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }
            updSiz(pos);
        }
    }
    int merge(int x, int y){
        if(!(x&&y)){
            return x+y;
        }
        if(rnk[x] < rnk[y]){
            rs[x] = merge(rs[x], y);
            updSiz(x);
            return x;
        }else{
            ls[y] = merge(x, ls[y]);
            updSiz(y);
            return y;
        }
    }
    long long del(long long k){
        static int x, y, now, a, b, c, tem;
        static long long res;
        split(a, b, k-1, root);
        now = a;
        while(rs[now]){
            now = rs[now];
        }
        x = now;
        now = b;
        while(ls[now]){
            now = ls[now];
        }
        y = now;
        if(!b || k-val[x] <= val[y]-k && a){
            split(c, tem, val[x]-1, a);
            root = merge(c, b);
            res = k-val[x];
        }else{
            split(tem, c ,val[y], b);
            root = merge(a, c);
            res = val[y]-k;
        }
        return res;
    }
};

void read(int &x);
void read(long long &x);

int main(){
    static const long long mod = 1000000;
    static int n;
    static long long ans;
    static FhqTreap tr;
    read(n);
    while(n--){
        static int opt, now;
        static long long x;
        read(opt), read(x);
        opt = opt?1:-1;
        if(now>=0&&opt>0 || now<=0&&opt<0){
            static int a, b;
            tr.split(a, b, x, tr.root);
            tr.root = tr.merge(tr.merge(a, tr.newNode(x)), b);
        }else{
            ans = (int)((long long)ans + tr.del(x))%mod;
        }
        now += opt;
    }
    printf("%lld", ans);
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

void read(long long &x){
    long long s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s;
}