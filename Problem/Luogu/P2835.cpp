//
// Created by kibi on 2022/10/27.
//
#include <bits/stdc++.h>

namespace Wr{

//    TODO bcj is not correct, maybe a way to make it correct
//    hack?, 自己推啦, 别看这个
//    5 2 0 5 0 0 5 0 3 4 0
//    4 2 0 4 0 2 0 1 0

    const int Size = 205;

    void read(int &x);

    int lib[Size];
    int find(int x);

    int main(){

        int n;
        read(n);
        for(int i = 0; i < n; ++i){
            lib[i+1] = i+1;
        }
        for(int i = 0; i < n; ++i){
            static int t;
            read(t);
            while(t){
                //            static int tem;
                //            tem = find(i+1);
                //            lib[t] = lib[t] == t ? tem : lib[t];
                lib[t] = find(i+1);
                read(t);
            }
        }
        int ans = 0;
        static std::unordered_map<int, bool> m;
        for (int i = 0; i < n; ++i) {
            if(!m[find(lib[i+1])]){
                m[find(lib[i+1])] = true;
                ++ans;
            }
        }
        printf("%d", ans);
    }

    int find(int x){
        return lib[x] != x ? (lib[x] = find(lib[x])) : x;
        //    return lib[x] != x ? (find(lib[x])) : x;
    }

    void read(int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }
}

//#include <bits/stdc++.h>

void read(int &x);

const int SizeN = 205;

class Graph {
    int head[SizeN], nxt[SizeN*SizeN], to[SizeN*SizeN], tot;

public:
    /*
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
    Graph *rawG;
    int sta[SizeN], inS[SizeN], r, dfn[SizeN], low[SizeN], id[SizeN], cntNode, cntId;
    void f(int u){
        dfn[u] = low[u] = ++cntNode;
        sta[++r] = u;
        inS[u] = true;
        for(int i = rawG->begin(u); i; i = rawG->next(i)){
            int v = rawG->get(i);
            if(!dfn[v]){
                f(v);
                low[u] = std::min(low[u], low[v]);
            }else if(inS[v]){
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]){
            ++cntId;
            while(sta[r] != u){
                id[sta[r]] = cntId, inS[sta[r]] = false;
                --r;
            }
            id[sta[r]] = cntId, inS[sta[r]] = false;
            --r;
        }
    }
public:
    int ans;
    void work(Graph *gT, int n){
        this -> rawG = gT;
        for(int i = 1; i <= n; i++){
            if(!dfn[i]){
                f(i);
            }
        }
        //        static std::unordered_map<std::pair<int, int>, bool> j;
        bool flag[SizeN];
        for(int i = 1; i <= n; i++){
            for(int now = rawG->begin(i); now; now = rawG->next(now)){
                static int v;
                v = rawG->get(now);
                //                g.addEdge(id[i], id[v]);
                if(id[i] != id[v]) {
                    flag[id[v]] = true;
                }
            }
        }

        for(int i = 1; i <= cntId; i++){
            if(!flag[i]){
                ans++;
            }
        }
    }
};

int main(){
    int n;
    static Graph g;
    read(n);
    for(int i = 1; i <= n; i++){
        static int t;
        read(t);
        while(t){
            g.addEdge(i, t, false);
            read(t);
        }
    }
    static Solution solve;
    solve.work(&g, n);
    printf("%d", solve.ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}