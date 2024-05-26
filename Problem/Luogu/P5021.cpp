//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 50000;

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
            int v, w;
            Edge *nxt;
        };
        Edge *head[N + 5];
        Edge edge[2 * N + 5];
        int cnt, size[N + 5];

        friend class Work;

    public:
        void add_edge(int u, int v, int w, bool flag = false){
            edge[++cnt] = {v, w, head[u]};
            head[u] = &edge[cnt];
            size[u]++;

            if(!flag){
                return;
            }

            add_edge(v, u, w);
        }
    };

    auto read = Tools::read;

    static int n, m, sum;
    read(n), read(m);

    static Graph graph;
    for(int i = 1; i < n; i++){
        static int u, v, w;
        read(u), read(v), read(w);
        sum += w;
        graph.add_edge(u, v, w, true);
    }

    static int length;
    static bool check_res;

    class Work{
    public:
        static void dfs(int u, int fa){
            static int val[N + 5], res;
            if(!fa){
                memset(val, 0, (n + 1) * (sizeof (int)));
                res = 0;
            }
            if(!(graph.size[u] - (fa ? 1 : 0))){
                val[u] = graph.head[u]->w;
                return;
            }
            Graph::Edge *edge_to_fa;
            vector<int> sort_val(graph.size[u] - (fa ? 1 : 0));
            int cnt = 0;
            for(auto i = graph.head[u]; i; i = i->nxt){
                if(i->v == fa) {
                    edge_to_fa = i;
                }else{
                    dfs(i->v, u);
                    sort_val[cnt++] = val[i->v];
                }
            }
            sort(sort_val.begin(), sort_val.end());
            vector<int> rest(graph.size[u] - (fa ? 1 : 0));
            cnt = -1;
            for(int i : sort_val){
                if(i >= length){
                    res++;
                }else {
                    rest[++cnt] = i;
                }
            }

            vector<bool> vis(cnt + 1);
            for(int i = 0; i < cnt; i++){
                if(!vis[i]){
                    int l = i + 1, r = cnt, pst = cnt + 1;
                    while(l <= r){
                        int mid = (l + r) >> 1;
                        if(rest[mid] + rest[i] >= length){
                            r = mid - 1, pst = mid;
                        }else{
                            l = mid + 1;
                        }
                    }
                    while(vis[pst]){
                        pst++;
                    }
                    if(pst <= cnt){
                        res++;
                        vis[i] = vis[pst] = true;
                    }
                }
            }

            if(!fa){
                if(res >= m){
                    check_res = true;
                }else{
                    check_res = false;
                }
                return;
            }

            int ready_to_push_up = 0;
            for(int i = cnt; i >= 0; i--){
                if(!vis[i]){
                    ready_to_push_up = rest[i];
                    break;
                }
            }

            val[u] = ready_to_push_up + edge_to_fa->w;

        }
    };

    mt19937 rnd(random_device{}());

    int l = 0, r = sum, ans;
    while(l <= r){
        int mid = (l + r) >> 1, rt = ((int)(rnd() % n + n) % n + 1);
        length = mid;
        Work::dfs(rt, 0);
        if(check_res){
            l = mid + 1, ans = mid;
        }else{
            r = mid - 1;
        }
    }

    printf("%d\n", ans);

}