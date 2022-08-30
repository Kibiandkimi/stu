//
// Created by kibi on 22-8-30.
//
#include <bits/stdc++.h>
using namespace std;
//struct Tree{
//    int l, r, ls, rs, s;
//}tr[2000005];
struct Node{
    int dep, fa, siz, son, id, top, se;
}dot[500005];
struct Ret {
    int p, c;
};
int n, m, cnt;
vector<int> g[500005];

bool getType(int c);
void read(int &x);
void f1(int u);
void f2(int u, int t);
int lca(int u, int v);
//void build(int u, int l, int r);
//int query(int u, int l, int r);
//int getMax(int x, int y, int z);
//Ret op1(int x, int y, int z);

int main(){
    read(n), read(m);
    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f1(1);
    f2(1, 1);
    //    build(1, 1, n);
    while(m--){
        int x, y, z;
        read(x), read(y), read(z);
        int xy = lca(x, y), xz = lca(x, z), yz = lca(y, z), ans = 0, o;
        if(xy == xz){
            o = yz;
            ans += dot[yz].dep*2 - dot[y].dep - dot[z].dep + dot[xy].dep*2 - dot[x].dep - dot[yz].dep;
        }else if(xy == yz){
            o = xz;
            ans += dot[xz].dep*2 - dot[x].dep - dot[z].dep + dot[xy].dep*2 - dot[y].dep - dot[xz].dep;
        }else{
            o = xy;
            ans += dot[xy].dep*2 - dot[y].dep - dot[x].dep + dot[xz].dep*2 - dot[z].dep - dot[xy].dep;
        }
        printf("%d %d\n", o, -ans);
    }
    return 0;
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void f1(int u){
    Node &o = dot[u];
    o.dep = dot[o.fa].dep+1;
    o.siz = 1;
    o.se = g[u].size();
    for(int i = 0; i < o.se; i++){
        int v = g[u][i];
        if(v != o.fa){
            dot[v].fa = u;
            f1(v);
            o.siz += dot[v].siz;
            if(dot[v].siz > dot[o.son].siz){
                o.son = v;
            }
        }
    }
}

void f2(int u, int t){
    Node &o = dot[u];
    o.top = t, o.id = ++cnt;
    //    rnk[cnt] = u;
    if(!o.son){
        return ;
    }
    f2(o.son, t);
    for(int i = 0; i < o.se; i++){
        int v = g[u][i];
        if(!dot[v].id){
            f2(v, v);
        }
    }
}

int lca(int u, int v) {
    while(dot[u].top != dot[v].top){
        if(dot[dot[u].top].dep > dot[dot[v].top].dep){
            u = dot[dot[u].top].fa;
        }else{
            v = dot[dot[v].top].fa;
        }
    }
    if(dot[u].dep > dot[v].dep){
        return v;
    }else{
        return u;
    }
}

//void build(int u, int l, int r){
//    Tree &o = tr[u];
//    o.l = l, o.r = r, o.s = 0;
//    if(l == r){
//        return;
//    }
//    int mid = (l+r)/2;
//    o.ls = u*2, o.rs = u*2+1;
//    build(o.ls, l, mid);
//    build(o.rs, mid+1, r);
//}

//void query(){}

//int getMax(int x, int y, int z){
//    if(x>=y&&x>=z){
//        return 1;
//    }else if(y>=z){
//        return 2;
//    }else{
//        return 3;
//    }
//}

//TODO 尝试重写op1

//Ret op1(int x, int y, int z){
//    int jump(int &from, int to = -1);
//    int getDifferent(int x, int y, int z);
//    int ans = 0, o = -1;
//    while(dot[x].top != dot[y].top && dot[y].top != dot[z].top){
//        int d = getMax(dot[dot[x].top].dep, dot[dot[y].top].dep, dot[dot[z].top].dep);
//        if(d == 1){
//            ans += jump(x);
//        }else if(d == 2){
//            ans += jump(y);
//        }else{
//            ans += jump(z);
//        }
//    }
//    int t = getDifferent(dot[x].top, dot[y].top, dot[z].top);
//    if(t != -1){
//        int &now = t==1?x:t==2?y:z, oth = t==1?y:t==2?z:x;
//        while(dot[now].top!=dot[oth].top && dot[dot[now].top].dep > dot[dot[oth].top].dep){
//            ans += jump(now);
//        }
//    }
//    int nx, ny;
//    if(dot[x].top == dot[y].top && dot[y].top == dot[z].top){
//        int d = getMax(dot[x].dep, dot[y].dep, dot[z].dep);
//        if(d == 1){
//            if(dot[y].dep > dot[z].dep){
//                ans += jump(x, y);
//                nx = y, ny = z, o = y;
//            }else if(dot[y].dep < dot[z].dep){
//                ans += jump(x, z);
//                nx = z, ny = y, o = z;
//            }else{
//                nx = x, ny = y, o = y;
//            }
//        }else if(d == 2){
//            if(dot[x].dep > dot[z].dep){
//                ans += jump(y, x);
//                nx = x, ny = z, o = x;
//            }else if(dot[z].dep > dot[x].dep){
//                ans += jump(y, z);
//                nx = z, ny = x, o = z;
//            }else{
//                nx = y, ny = x, o = z;
//            }
//        }else{
//            if(dot[x].dep > dot[y].dep){
//                ans += jump(z, x);
//                nx = x, ny = y, o = x;
//            }else if(dot[x].dep < dot[y].dep){
//                ans += jump(z, y);
//                nx = x, ny = y, o = y;
//            }else{
//                nx = z, ny = x, o = y;
//            }
//        }
//    }else if(dot[x].top == dot[y].top){
////        nx = x, ny = z;
//        if(dot[x].dep>dot[y].dep){
//            ans += jump(x, y);
//        }else if(dot[x].dep < dot[y].dep){
//            ans += jump(y, x);
//        }
//        nx = x, ny = z, o = x;
//    }else if(dot[x].top == dot[z].top){
//        if(dot[x].dep>dot[z].dep){
//            ans += jump(x, z);
//        }else if(dot[z].dep > dot[x].dep){
//            ans += jump(z, x);
//        }
//        nx = x, ny = y, o = x;
//    }else{
//        if(dot[y].dep > dot[z].dep){
//            ans += jump(y, z);
//        }else if(dot[y].dep < dot[z].dep){
//            ans += jump(z, y);
//        }
//        nx = x, ny = y, o = y;
//    }
//
//    while(dot[nx].top != dot[ny].top){
//        if(dot[dot[nx].top].dep > dot[dot[ny].top].dep){
//            ans += jump(nx);
//        }else{
//            ans += jump(ny);
//        }
//    }
//
//    if(dot[nx].dep>dot[ny].dep){
//        ans += jump(nx, ny);
//    }else if(dot[ny].dep > dot[nx].dep){
//        ans += jump(ny, nx);
//    }
//    Ret e = {o, ans};
//    return e;
//}

//int jump(int &from, int to = -1){
//    if(to == -1){
//        to = dot[dot[from].top].fa;
//    }
//    int res = dot[from].dep - dot[to].dep;
//    from = to;
//    return res;
//}
//
//int getDifferent(int x, int y, int z){
//    if(x == y && y == z){
//        return -1;
//    }
//    if(x == y){
//        return 3;
//    }else if(x == z){
//        return 2;
//    }else{
//        return 1;
//    }
//}