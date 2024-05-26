//
// Created by kibi on 2021/8/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,p[50005],d[50005],fa[50005][30];
vector<int> a[50005];
void pre(int x, int f){
    d[x] = d[f]+1;
    fa[x][0] = f;
    for(int i = 0; fa[x][i]; i++){
        fa[x][i+1] = fa[fa[x][i]][i];
    }
    int sa = a[x].size();
    for(int i = 0; i < sa; i++){
        if(a[x][i]!=f){
            pre(a[x][i], x);
        }
    }
}
int lca(int t1, int t2){
    int u,v;
    u = d[t1]>d[t2]?t2:t1;
    v = t1+t2-u;
    for(int i = 20; i >= 0; i--){
        if(d[u]<=d[v]-(1<<i)){
            v = fa[v][i];
        }
    }
    if(u == v){
        return u;
    }
    for(int i = 20; i >= 0; i--){
        if(fa[u][i]!=fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
int f(int x, int fa){
    int sa = a[x].size();
    int s = 0;
    for(int i = 0; i < sa; i++){
        if(a[x][i]==fa)continue;
        s = max(s, f(a[x][i], x));
        p[x] += p[a[x][i]];
    }
    s = max(s, p[x]);
    return s;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    pre(1, 0);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        int l = lca(u,v);
        p[u]++;
        p[v]++;
        p[l]--;
        p[fa[l][0]]--;
    }
    printf("%d", f(1,0));
}


// 2023/7/19

/*
 * #include <bits/stdc++.h>
using namespace std;

const int N = 50000;

void read(int&);

int main(){

    class Tree{
        int head[N+5], nxt[2*N+5], to[2*N+5], cnt;
        int dep[N+5], fo[N+5][21];
        int sum[N+5], val[N+5];

        void f(int u, int fa){
            dep[u] = dep[fa]+1;
            fo[u][0] = fa;
            for(int i = 1; i <= 20; i++){
                fo[u][i] = fo[fo[u][i-1]][i-1];
            }
            for(int i = head[u]; i; i = nxt[i]){
                if(to[i] != fa){
                    f(to[i], u);
                }
            }
        }

        int f2(int u, int fa){
            static int res = 0;
            if(fa == 0){
                res = 0;
            }
            sum[u] = val[u];
            for(int i = head[u]; i; i = nxt[i]){
                if(to[i] != fa){
                    f2(to[i], u);
                    sum[u] += sum[to[i]];
                }
            }
            res = max(res, sum[u]);
            return res;
        }

    public:

        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void init_lca(){
            f(1, 0);
        }

        int lca(int x, int y){
            if(dep[x] > dep[y]){
                swap(x, y);
            }
            for(int i = 20; i >= 0; i--){
                if(dep[fo[y][i]]>=dep[x]){
                    y = fo[y][i];
                }
            }
            if(x == y){
                return x;
            }
            for(int i = 20; i >= 0; i--){
                if(fo[x][i] != fo[y][i]){
                    //                    x = fo[fo[x][i]][0], y = fo[fo[y][i]][0]; TODO  why not
                    x = fo[x][i], y = fo[y][i];
                }
            }
            return fo[x][0];
        }

        int work(){
            return f2(1, 0);
        }

        void add_val(int x, int v){
            val[x] += v;
        }

        //        int begin(int x){
        //            return head[x];
        //        }
        //
        //        int next(int x){
        //            return nxt[x];
        //        }
        //
        //        int get(int x){
        //            return to[x];
        //        }

        int get_fa(int x){
            return fo[x][0];
        }
    };

    static Tree tree;
    int n, k;

    read(n), read(k);

    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        tree.add_edge(u, v);
    }

    tree.init_lca();

    for(int i = 1; i <= k; i++){
        int s, t, lca;
        read(s), read(t);
        lca = tree.lca(s, t);
        tree.add_val(lca, -1);
        tree.add_val(tree.get_fa(lca), -1);
        tree.add_val(s, 1);
        tree.add_val(t, 1);
        //        if(s != lca) {
        //            for (int j = tree.begin(s); j; j = tree.next(j)) {
        //                int v = tree.get(j);
        //                if (v != tree.get_fa(s)) {
        //                    tree.add_val(v, -1);
        //                }
        //            }
        //        }
        //        if(t != lca) {
        //            for (int j = tree.begin(t); j; j = tree.next(j)) {
        //                int v = tree.get(j);
        //                if (v != tree.get_fa(t)) {
        //                    tree.add_val(v, -1);
        //                }
        //            }
        //        }
    }

    int ans = tree.work();

    printf("%d\n", ans);

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
 * */