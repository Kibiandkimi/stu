//
// Created by kibi on 22-8-10.
//
//pts84 the code is same us P5049
#include <bits/stdc++.h>
using namespace std;
int n, m;
bool vis[6005], in_r[6005], flag_sp, st_sp;
int ans[6005], cnt = 1, st_r;
vector<int> g[6005];
stack<int> s;
stack<int> sec_min;

bool cmp(int a, int b){
    return a < b;
}

void f(int u){
    int sg = g[u].size();
    vis[u] = true;
    ans[cnt++] = u;
    for(int i = 0; i < sg; i++){
        if(!vis[g[u][i]]) {
            f(g[u][i]);
        }
    }
}

int find_r(int u, int fa){
    int sg = g[u].size();
    s.push(u);
    vis[u] = true;
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        if(vis[g[u][i]]){
            in_r[s.top()] = true;
            s.pop();
            st_r = g[u][i];
            return g[u][i];
        }else{
            if(int t = find_r(g[u][i], u)){
                if(t == -1){
                    return -1;
                }
                in_r[s.top()] = true;
                s.pop();
                if(t == u){
                    return -1;
                }
                return t;
            }
        }
    }
    s.pop();
    return 0;
}

void sp_f(int u){
    vis[u] = true;
    ans[cnt++] = u;
    int sg = g[u].size();
    if((!sec_min.empty())&&sec_min.top() == u){
        sec_min.pop();
    }
    if(u == st_r){
        flag_sp = true;
        int t;
        for(t = 0; vis[g[u][t]]; t++){}
        for(int i = t; i < sg; i++){
            if(!vis[g[u][i]]) {
                if(in_r[g[u][i]] && i+1 < sg && !st_sp) {
                    sec_min.push(g[u][i + 1]);
                }
                sp_f(g[u][i]);
            }
        }
    }
    if(flag_sp&&!st_sp){
        int t;
        for(t = 0; vis[g[u][t]]; t++){}
        for(int i = t; i < sg; i++){
            if(vis[g[u][i]]){
                continue;
            }
            if(in_r[g[u][i]]){
                if(sg>i+1) {
                    sec_min.push(g[u][i + 1]);
                }
            }
            if(in_r[g[u][i]] && g[u][i] > sec_min.top()){
                st_sp = true;
                continue;
//                if(i == sg-1){
//                    return ;
//                }else{
//                    vis[g[u][i]] = true;
//                    ans[cnt++] = g[u][i];
//                    for(int j = i+1; j < sg; j++){
//                        if(!vis[g[u][j]]){
//                            sp_f(g[u][j]);
//                        }
//                    }
//                    return;
//                }
            }
            sp_f(g[u][i]);
        }
    }else {
        for (int i = 0; i < sg; i++) {
            if (!vis[g[u][i]]) {
                sp_f(g[u][i]);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        sort(g[i].begin(), g[i].end(), cmp);
    }
    if(n-1 == m) {
        f(1);
    }else{
        find_r(1, 0);
        memset(vis, 0, sizeof vis);
        sp_f(1);
    }
    for(int i = 1; i <= n; i++){
        printf("%d ", ans[i]);
    }
}

// 2023/9/28

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 5000;

    class Tools{
    public:
        static void read(int &x){
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
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt, *pre;
        };
        Edge *head[N + 5];
        Edge edge[2 * N + 5];
        int cnt;

        friend class Work;

    public:
        void add_edge(int u, int v, bool flag = false){
            edge[++cnt] = {v, head[u], nullptr};
            head[u] = &edge[cnt];

            if(edge[cnt].nxt) {
                edge[cnt].nxt->pre = head[u];
            }

            if(!flag){
                return;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    static int n, m;
    read(n), read(m);

    static Graph raw_graph, graph;
    for(int i = 1; i <= m; i++){
        static int u, v;
        read(u), read(v);
        raw_graph.add_edge(u, v, true);
    }

    static int ans[N + 5];

    class Work{
    public:
        static void sort_graph(){
            for(int i = 1; i <= n; i++){
                static int temp[N + 5];
                int cnt = 0;
                for(auto j = raw_graph.head[i]; j; j = j->nxt){
                    temp[cnt++] = j->v;
                }
                sort(temp, temp + cnt);
                for(int j = cnt - 1; j >= 0; --j){
                    graph.add_edge(i, temp[j]);
                }
            }
        }

        int *res;

        void dfs(int u, int fa){
            static int cnt;
            if(fa == 0){
                cnt = 0;
            }
            res[++cnt] = u;
            for(auto i = graph.head[u]; i; i = i->nxt){
                if(i->v != fa){
                    dfs(i->v, u);
                }
            }
        }

        static void dfs2(map<pair<int, int>, bool> &mp, int u, int fa){
            static bool vis[N + 5], on;
            static int rt;
            vis[u] = true;
            for(auto i = graph.head[u]; i; i = i->nxt){
                if(i->v != fa){
                    if(vis[i->v]){
                        rt = i->v;
                        mp[{u, i->v}] = mp[{i->v, u}] = true;
                        on = true;
                        return;
                    }
                    dfs2(mp, i->v, u);
                    if(rt){
                        if(on){
                            mp[{u, i->v}] = mp[{i->v, u}] = true;
                            if(rt == u){
                                on = false;
                            }
                        }
                        return;
                    }
                }
            }
        }

        static void deal_map(map<pair<int, int>, bool> &mp){
            dfs2(mp, 1, 0);
        }

        static void check(){

            map<pair<int, int>, bool> mp;
            deal_map(mp);

            static int res[N + 5];
            for(int i = 1; i <= n; i++){
                for(auto j = graph.head[i]; j; j = j->nxt){
                    if(mp[{i, j->v}]) {
                        for (auto k = graph.head[j->v]; k; k = k->nxt) {
                            if (k->v == i) {
                                if (j->pre == nullptr) {
                                    graph.head[i] = j->nxt;
                                } else {
                                    j->pre->nxt = j->nxt;
                                }
                                if (k->pre == nullptr) {
                                    graph.head[j->v] = k->nxt;
                                } else {
                                    k->pre->nxt = k->nxt;
                                }
                                Work{res};
                                if (j->pre == nullptr) {
                                    graph.head[i] = j;
                                } else {
                                    j->pre->nxt = j;
                                }
                                if (k->pre == nullptr) {
                                    graph.head[j->v] = k;
                                } else {
                                    k->pre->nxt = k;
                                }
                                break;
                            }
                        }
                        if (ans[1] == 0) {
                            for (int k = 1; k <= n; k++) {
                                ans[k] = res[k];
                            }
                        } else {
                            bool flag = false;
                            for (int k = 1; k <= n; k++) {
                                if (flag) {
                                    ans[k] = res[k];
                                } else if (ans[k] < res[k]) {
                                    break;
                                } else if (ans[k] > res[k]) {
                                    flag = true;
                                    ans[k] = res[k];
                                }
                            }
                        }
                    }
                }
            }
        }

        Work(int *res):res(res){
            dfs(1, 0);
        }
    };

    Work::sort_graph();

    if(n - 1 == m){
        Work{ans};
        for(int i = 1; i <= n; i++){
            printf("%d ", ans[i]);
        }
    }else{
        Work::check();
        for(int i = 1; i <= n; i++){
            printf("%d ", ans[i]);
        }
    }
}
 *
 * */