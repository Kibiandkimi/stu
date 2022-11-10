//
// Created by kibi on 2022/11/7.
//
#include <bits/stdc++.h>
using namespace std;

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
    //    Do not use it, need to repair
    void splitBySiz(int &x, int &y, int k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(siz[ls[pos]] >= k){
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }else{
                x = pos;
                split(rs[pos], y, k-siz[ls[pos]], rs[pos]);
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
    void add(int x){
        static int a, b;
        split(a, b, x, root);
        root = merge(merge(a, addNode(0, x)), b);
    }
    int queryByRnk(int k){

        /*
         * another way, but need to fix
        static int a, b, c, tem, res;
        splitBySiz(a, b, k-1, root);
        splitBySiz(tem, c, 1, b);
        res = pri[tem];
        root = merge(a, merge(tem, c));
        return res;
        */

        static int now;
        now = root;
        while(true){
            if(siz[ls[now]] >= k){
                now = ls[now];
            }else if(siz[ls[now]] + 1 == k){
                return pri[now];
            }else{
                k -= siz[ls[now]] + 1;
                now = rs[now];
            }
        }
    }
};

void read(int&);

int main(){
    static int n, m;
    static FhqTreap fhqTr;
    read(n);
    for(int i = 1; i <= n; i++){
        static int t;
        read(t);
        fhqTr.add(t);
    }
    read(m);
    for(int i = 1; i <= m; i++){
        static char opt[5];
        scanf("%s", opt);
        //        opt = getchar();
        //        getchar(), getchar(), getchar();
        if(opt[0] == 'a'){
            static int tem;
            read(tem);
            fhqTr.add(tem);
            n++;
        }else if(opt[0] == 'm'){
            static int tem;
            tem = fhqTr.queryByRnk(n/2 + (n%2));
            printf("%d\n", tem);
        }else{
            throw "error";
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