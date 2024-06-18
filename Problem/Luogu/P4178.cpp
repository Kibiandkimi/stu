//
// Created by Kibi on 24-5-26.
//
// TODO 24-6-18

// 用覆盖率测
// 疑似 main::get_barycentre 复杂度问题
// 答案也存在问题

#include <bits/stdc++.h>
using namespace std;

int main(){
    static auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c){
            if (c == '-'){
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
            Edge *nxt;
            int v, w;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{head[u], v, w};
            return flag ? add_edge(v, u, w) : void();
        }

        Edge* begin(int &u){
            return head[u];
        }
    };

    freopen("../IO/Luogu/P4178/P4178_1.in", "r", stdin);

    static int n, k, rt;
    read(n);

    static Graph graph(n);
    for(int i = 1; i < n; i++){
        static int u, v, w;
        read(u), read(v), read(w);
        u--, v--;
        graph.add_edge(u, v, w, true);
    }

    read(k);

    rt = int(random_device{}() % n);

    static auto solve = [](){
        static int ans;
        static stack<int> stk;
        static vector<bool> vis(n);
        static vector<int> siz(n), mxp(n);

        static auto get_barycentre = [](int u, int n){
            static int res;
            static stack<tuple<int, int, int>> stk; // 0->u, 1->fa, 2->stat

            res = -1;
            stk.emplace(u, -1, 0);
            while(!stk.empty()){
                auto [now, fa, stat] = stk.top();
                stk.pop();
                switch(stat){
                    case 0:
                        siz[now] = 1, mxp[now] = 0;
                        stk.emplace(now, fa, 1);
                        for(auto i = graph.begin(now); i; i = i->nxt){
                            if(i->v != fa && !vis[i->v]){
                                stk.emplace(i->v, now, 0);
                            }
                        }
                        break;
                    case 1:
                        mxp[now] = max(mxp[now], n - siz[now]);
                        res < 0 || mxp[now] > mxp[res] ? res = now : res;
                        fa ? siz[fa] += siz[now], mxp[fa] = max(mxp[fa], siz[now]) : 0 ;
                        break;
                    default:
                        throw runtime_error("Error state!");
                }
            }
            return res;
        };
        static auto calc = [](int u){
            static int l, r;
            static vector<int> dis(n), res;
            static stack<tuple<int, int>> stk; // 1->now, 2->fa

            static auto get_dis = [](int u){
                stk.emplace(u, -1);

                while(!stk.empty()){
                    auto [now, fa] = stk.top();
                    stk.pop();
                    res.emplace_back(dis[now]);
                    for(auto i = graph.begin(now); i; i = i->nxt){
                        if(i->v != fa && !vis[i->v]){
                            dis[i->v] = dis[now] + i->w;
                            stk.emplace(i->v, now);
                        }
                    }
                }
            };

            res.clear();
            dis[u] = 0;
            get_dis(u);

            sort(res.begin(), res.end());
            l = 0, r = (int)(res.size() - 1);
            while(l <= r){
                res[l] + res[r] <= k ? ans += r - l, ++l : --r;
            }

            for (auto i = graph.begin(u); i; i = i->nxt){
                if(!vis[i->v]){
                    dis[i->v] = i->w;
                    res.clear();
                    get_dis(i->v);
                    sort(res.begin(), res.end());
                    l = 0, r = (int)(res.size() - 1);
                    while(l <= r){
                        res[l] + res[r] <= k ? ans -= r - l, ++l : --r;
                    }
                }
            }

        };

        ans = 0;
        vis[rt] = true;
        siz[rt] = n;
        stk.emplace(rt);
        while(!stk.empty()){
            static int now, barycentre;

            now = stk.top();
            stk.pop();
            barycentre = get_barycentre(now, siz[now]);
            vis[barycentre] = true;
            calc(barycentre);

            for (auto i = graph.begin(barycentre); i; i = i->nxt){
                if(!vis[i->v]){
                    stk.emplace(i->v);
                }
            }
        }
        return ans;
    };

    int ans = solve();
    printf("%d\n", ans);

    fclose(stdin);
}