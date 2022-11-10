//
// Created by kibi on 2022/10/15.
//
#include <bits/stdc++.h>

namespace raw {
    using namespace std;
    int head[1005], nxt[30005], to[30005];
    bool g[1005][1005];
    int val[1005];
    void read(int &x);
    void addEdge(int u, int v);

    int main() {
        static int n, m, p, q;
        read(n), read(m), read(p), read(q);

        //    for subtask1
        if ((long long) n * p <= q) {
            printf("1");
            return 0;
        }

        //    memset(g, -1, sizeof g);
        for (int i = 1; i <= m; i++) {
            static int u, v;
            read(u), read(v);
            addEdge(u, v);
        }

        //    for subtask2
        for (int i = 1; i <= n; i++) {
            g[i][i] = true;
            bool flag = true;
            for (int j = 1; j <= n; j++) {
                if (!g[i][j]) {
                    flag = false;
                }
            }
            if (flag) {
                printf("%.7lf", (double) p * (n - 1) / (q - p));
                return 0;
            }
        }
    }

    void addEdge(int u, int v) {
        g[u][v] = g[v][u] = true;
    }

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }
}

namespace change1{
    using namespace std;
    const int SizeN = 1005, SizeM = 30005;
    class Graph {
        int head[SizeN], nxt[SizeM], to[SizeM], tot;

    public:/*
    Graph() {
        //         are these necessary?
        memset(head, 0, sizeof head);
        memset(to, 0, sizeof to);
        memset(nxt, 0, sizeof nxt);
        tot = 0;
    }
    */
        void addEdge(int u, int v, bool flag = true) {
            to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
            if (!flag) {
                return;
            }
            to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
        }
        int begin(int x) {
            return head[x];
        }
        int next(int x) {
            return nxt[x];
        }
        int get(int x) {
            return to[x];
        }
    };

    class Solution{
        Graph *g;
        int p, q, n;
        bool check(double x, int root){
            static queue<int> uQ, depQ;
            static double sum, rest = 1e9 * (double) p / (double) q;
            static bool vis[SizeN];
            static int rt;
            rt = root;
            while(!uQ.empty()){
                uQ.pop();
                depQ.pop();
            }
            memset(vis, 0, sizeof vis);
            sum = 0;
            uQ.push(rt);
            depQ.push(0);
            while(!uQ.empty() && sum <= rest){
                int u = uQ.front(), dep = depQ.front();
                uQ.pop(), depQ.pop();
                sum += pow(1/(double)x, dep) * rest;
                if(u == rt){
                    sum = 0;
                }
                for(int i = g->begin(u); i; i = g->next(i)){
                    int v = g->get(i);
                    if(!vis[v]){
                        vis[v] = true;
                        uQ.push(v), depQ.push(dep+1);
                    }
                }
            }
            if(sum <= rest){
                return true;
            }else{
                return false;
            }
        }
        bool work(double x){
            for(int i = 1; i <= n; i++){
                if(!check(x, i)){
                    return false;
                }
            }
            return true;
        }
    public:
        double ans;
        Solution(Graph *gT, int p, int q, int n){
            this -> p = p, this -> q = q, this -> n = n;
            g = gT;
            double l = 1, r = 10000005;
            while(l < r){
                static double mid;
                mid = (l+r)/2;
                if(work(mid)){
                    r = mid;
                }else{
                    l = mid + 0.00001;
                }
            }
            ans = l;
        }
    };

    void read(int &x);

    int main(){
        static int n, m, p, q;
        static Graph g;
        read(n), read(m), read(p), read(q);
        for(int i = 1; i <= m; i++){
            int u, v;
            read(u), read(v);
            g.addEdge(u, v);
        }
        Solution solve(&g, p, q, n);
        printf("%.7lf", solve.ans);
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

}