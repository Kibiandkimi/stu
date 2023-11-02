//
// Created by kibi on 23-11-2.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

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

        static int rand(int x){
            return (int)((rnd() % x + x) % x + 1);
        }
    };

    class Graph{
        class Node{
        public:
            int id, v;
            Node *nxt;
        };

        int cnt;
        vector<Node*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr), cnt(1){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Node{(++cnt) >> 1, v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Node* begin(int u){
            return head[u];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, new_id;
            bool vis;
        };

        int n, num;
        Graph *graph;
        vector<Node> node;
        vector<int> sum;

        void dfs(Node *u, Node *fa, int id_of_edge){
            static int cnt = 0;
            static stack<int> stk;
            u->dfn = u->low = ++cnt;
            stk.push(u->id);
            u->vis = true;

            for(auto i = graph->begin(u->id); i; i = i->nxt){
                Node *v = &node[i->v];
                if(i->id == id_of_edge){
                    continue;
                }
                if(!v->dfn){
                    dfs(v, u, i->id);
                    u->low = min(u->low, v->low);
                }else if(v->vis){
                    u->low = min(u->low, v->dfn);
                }
            }

            if(u->dfn == u->low){
                ++num;
                int x;
                sum.emplace_back(0);
                do {
                    x = stk.top();
                    stk.pop();
                    node[x].vis = false;
                    node[x].new_id = num;
                    sum[num]++;
                } while(x != u->id);
            }
        }

    public:
        Tarjan(int n, int rt, Graph *graph):n(n), graph(graph), node(n + 1), num(0), sum(1){
            for(int i = 1; i <= n; i++){
                node[i] = {i, 0, 0, 0, false};
            }

            dfs(&node[rt], nullptr, 0);

            for(int i = 1; i <= n; i++){
                if(!node[i].dfn){
                    dfs(&node[i], nullptr, 0);
                }
            }
        }

        friend class Work;
    };

    auto read = Tools::read;
    auto rand = Tools::rand;

    int n, m;
    read(n), read(m);

    Graph graph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    Tarjan tarjan(n, rand(n), &graph);

    class Work{
    public:
        explicit Work(Tarjan *tarjan){
            vector<vector<int>> data(tarjan->num, vector<int>{});
            for(int i = 1; i <= tarjan->n; i++){
                data[tarjan->node[i].new_id - 1].push_back(tarjan->node[i].id);
            }
            printf("%d\n", tarjan->num);
            for(int i = 0; i < tarjan->num; i++){
                printf("%d ", tarjan->sum[i + 1]);
                for(auto &j : data[i]){
                    printf("%d ", j);
                }
                printf("\n");
            }
        }
    };

    Work{&tarjan};

}