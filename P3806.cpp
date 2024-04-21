//
// Created by Lenovo on 24-4-18.
//
// TODO 24-4-21
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
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
    };

    class Graph{
        class Edge{
        public:
            int v, w;
            Edge *nxt;
        };
        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(const int &u, const int &v, const int &w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};
            return flag ? add_edge(v, u, w) : void();
        }

        Edge* begin(int u) const{
            return head[u];
        }
    };

    class Question {
    public:
        int k;
        bool ans;
    };

    mt19937 rnd(random_device{}());

    static int n, m, rt;
    read(n), read(m);

    static vector<Question> que(m);
    static Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(--u, --v, w, true);
    }
    for(auto &i : que){
        read(i.k);
        i.ans = !i.k;
    }

    static vector<bool> vis(n);
    static vector<int> siz(n), mxp(n); // siz->tree_size mxp->max_subtree_size
    static auto get_barycentre = [](int u, int n){
        int res = -1;
        using stat = tuple<int, int, int>; // 1->u, 2->fa, 3->stat
        stack<stat> stk;
        stk.emplace(u, -1, 0);
        while(!stk.empty()){
            auto [now, fa, step] = stk.top();
            stk.pop();
            switch(step){
                case 0:
                    siz[now] = 1, mxp[now] = 0;
                    stk.emplace(now, fa, 1);
                    for(auto i = graph.begin(now); i; i = i->nxt){
                        if(i->v == fa || vis[i->v]){
                            continue;
                        }
                        stk.emplace(i->v, now, 0);
                    }
                    break;
                case 1:
                    mxp[now] = max(mxp[now], n - siz[now]);
                    if(res < 0 || mxp[now] < mxp[res]){
                        res = now;
                    }
                    fa > -1 ? siz[fa] += siz[now] : 0;
                    break;
                default:
                    throw runtime_error("Error state!");
            }
        }
        return res;
    };

    static auto solve = [](int u){

        static auto calc = [](int u){
            static vector<int> a, b(n), d(n);
            static auto get_dis = [](int u, int _fa, int _dis, int from){
                using stat = tuple<int, int, int>; // 1->now, 2->fa, 3->dis
                stack<stat> stk;
                stk.emplace(u, _fa, _dis);
                while(!stk.empty()){
                    auto [now, fa, dis] = stk.top();
                    stk.pop();
                    a.emplace_back(now);
                    d[now] = dis;
                    b[now] = from;
                    for(auto i = graph.begin(now); i; i = i->nxt){
                        if(i->v == fa || vis[i->v]){
                            continue;
                        }
                        stk.emplace(i->v, now, dis + i->w);
                    }

                }
            };

            a.clear();
            a.emplace_back(u);
            d[u] = 0;
            b[u] = u;
            for(auto i = graph.begin(u); i; i = i->nxt){
                if(vis[i->v]){
                    continue;
                }
                get_dis(i->v, u, i->w, i->v);
            }

            sort(a.begin(), a.end(), [](const int &a, const int &b){return d[a] < d[b];});
            for(auto &i : que){
                int l = 0, r = (int)a.size() - 1;
                if(i.ans){
                    continue;
                }
                while(l < r){
                    if(d[a[l]] + d[a[r]] > i.k){
                        r--;
                    }else if(d[a[l]] + d[a[r]] < i.k){
                        l++;
                    }else if(b[a[l]] == b[a[r]]){
                        d[a[r]] == d[a[r - 1]] ? r-- : l++;
                    }else{
                        i.ans = true;
                        break;
                    }
                }
            }
        };

        stack<int> stk;
        stk.emplace(u);
        while(!stk.empty()){
            int now = stk.top();
            stk.pop();
            vis[now] = true;
            calc(now);
            for(auto i = graph.begin(now); i; i = i->nxt){
                if(vis[i->v]){
                    continue;
                }
                stk.emplace(get_barycentre(i->v, siz[i->v]));
            }
        }
    };

    rt = (int)(rnd() % n);
    solve(get_barycentre(rt, n));

    for(auto &i : que){
        printf(i.ans ? "AYE\n" : "NAY\n");
    }

}