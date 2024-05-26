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

        static int rand(int v){
            return (int)((rnd() % v + v) % v + 1);
        }
    };

    class Graph{
        class Node{
        public:
            int v;
            Node *nxt;
        };

        vector<Node*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Node{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Node* begin(int x){
            return head[x];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, num_son;
            vector<int> new_id;
            bool vis;
        };

        int n, num;
        Graph *graph;
        vector<Node> node;
        vector<int> sum;

        void dfs(Node *u, Node *fa){
            static int cnt = 0;
            static stack<int> stk;
            u->dfn = u->low = ++cnt;
            u->vis = true;
            stk.push(u->id);

            for (auto i = graph->begin(u->id); i; i = i->nxt) {
                Node *v = &node[i->v];
                if(!v->dfn){
                    u->num_son++;
                    dfs(v, u);
                    u->low = min(u->low, v->low);
                    if(v->low >= u->dfn){
                        ++num;
                        int x = 0;
                        sum.emplace_back(1);
                        while(x != v->id){
                            x = stk.top();
                            stk.pop();
                            node[x].new_id.emplace_back(num);
                            sum[num]++;
                        }
                        node[u->id].new_id.emplace_back(num);
                    }
                }else if(v != fa){
                    u->low = min(u->low, v->dfn);
                }
            }

            if(fa == nullptr && u->num_son == 0){
                ++num;
                node[u->id].new_id.emplace_back(num);
                sum.emplace_back(1);
            }
        }

    public:
        Tarjan(int rt, int n, Graph *graph):n(n), node(n + 1), sum(1, 0), graph(graph), num(0){
            for(int i = 1; i <= n; i++){
                node[i] = {i, 0, 0, 0, {}, false};
            }

            dfs(&node[rt], nullptr);

            for(int i = 1; i <= n; i++){
                if(!node[i].dfn){
                    dfs(&node[i], nullptr);
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

    Tarjan tarjan(rand(n), n, &graph);

    class Work{
    public:
        explicit Work(Tarjan *tarjan){
            printf("%d\n", tarjan->num);
            vector<vector<int>> data(tarjan->num, vector<int>{});
            for(int i = 1; i <= tarjan->n; i++){
                for(auto &j : tarjan->node[i].new_id) {
                    data[j - 1].emplace_back(tarjan->node[i].id);
                }
            }
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