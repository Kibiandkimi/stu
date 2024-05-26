//
// Created by kibi on 23-10-3.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 1000000;

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

        static int limit(int raw, int n){
            return ((raw % n + n) % n) + 1;
        }
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        Edge *head[N + 5];

        friend class Work;

    public:
        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }
    };

    freopen("orient.in", "r", stdin);
    freopen("orient.out", "w", stdout);

    auto read = Tools::read;

    static int n;
    read(n);

    static Graph graph;
    for(int i = 1; i < n; ++i){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    static long long ans;
    int raw_siz[n];
    static int *siz = (raw_siz - 1);


    class Work{

    public:

        void dfs(int u, int fa){
            siz[u] = 1;
            for(auto i = graph.head[u]; i; i = i->nxt){
                if(i->v != fa){
                    dfs(i->v, u);
                    siz[u] += siz[i->v];
                    ans += (long long)siz[i->v] * siz[i->v];
                }
            }
            ans += (long long)(n - siz[u]) * (n - siz[u]);
            ans += 2 * n - 1;
        }

        Work(){
            mt19937 rnd(random_device{}());

            dfs(Tools::limit((int)rnd(), n), 0);
        }
    };

    Work();

    printf("%lld\n", ans);

    fclose(stdin);
    fclose(stdout);
}