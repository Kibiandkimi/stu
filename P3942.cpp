//
// Created by Lenovo on 24-4-14.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c){
            if(c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};
            return flag ? add_edge(v, u) : void();
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    static int n, k, t;
    read(n), read(k), read(t);

    Graph graph(n);
    for(int i = 1; i < n; i++){
        static int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    int raw_dep[n], raw_fa[n];
    static auto dep = raw_dep - 1, fa = raw_fa - 1;
    dep[1] = 0, fa[1] = 1;
    auto dfs1 = [&](int x){
        stack<int> stk;
        stk.emplace(x);
        while(!stk.empty()){
            auto u = stk.top();
            stk.pop();
            dep[u] = dep[fa[u]] + 1;
            for(auto i = graph.begin(u); i; i = i->nxt){
                if(i->v != fa[u]){
                    fa[i->v] = u;
                    stk.emplace(i->v);
                }
            }
        }
    };
    dfs1(1);

    class Cmp{
    public:
        bool operator ()(const int &a, const int &b){
            return dep[a] < dep[b];
        }
    };
    priority_queue<int, vector<int>, Cmp> q;
    for(int i = 1; i <= n; i++){
        q.emplace(i);
    }

    int ans = 0;
    bool raw_vis[n], raw_is_ans[n];
    int raw_tem_vis[n];
    auto vis = raw_vis - 1, is_ans = raw_is_ans - 1;
    auto tem_vis = raw_tem_vis - 1;
    memset(raw_vis, 0, sizeof raw_vis);
    memset(raw_is_ans, 0, sizeof raw_is_ans);
    while(!q.empty()){
        int now = q.top();
        q.pop();
        while(!q.empty() && vis[now]){
            now = q.top();
            q.pop();
        }
        if(vis[now]){
            break;
        }

        bool flag = false;
        for(int i = 0; i < k; i++){
            now = fa[now];
            if(is_ans[now]){
                flag = true;
                break;
            }
        }
        if(flag){
            continue;
        }
        vis[now] = true;
        tem_vis[now] = now;
        is_ans[now] = true;
        ans++;

        auto dfs2 = [&](int x){
            if(x == 1){
                return ;
            }
            stack<tuple<int, int>> stk;
            vis[fa[x]] = true;
            tem_vis[fa[x]] = x;
            stk.emplace(fa[x], 1);
            while(!stk.empty()){
                auto [u, step] = stk.top();
                stk.pop();
                if(step < k){
                    for(auto i = graph.begin(u); i; i = i->nxt){
                        if(tem_vis[i->v] != x && !is_ans[i->v]){
                            stk.emplace(i->v, step + 1);
                            vis[i->v] = true;
                            tem_vis[i->v] = x;
                        }
                    }
                }
            }
        };
        dfs2(now);
    }

    printf("%d\n", ans);
}