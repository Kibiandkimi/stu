//
// Created by kibi on 23-8-16.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 500000;

    class Graph{
        class Node{
        public:
            int id;
            Node(){
                id = -1;
            }
            explicit Node(int id):id(id){}
        };
        class Edge{
        public:
            Node* to;
            Edge* nxt;
        };
        Edge *head[N + 5]{};
        Edge edge[N + 5]{};
        Node node[N + 5];
        int cnt{0};

    public:

        void add_edge(int u, int v, bool flag = false){
            if(node[u].id == -1){
                node[u].id = u;
                head[u] = nullptr;
            }

            if(node[v].id == -1){
                node[v].id = v;
                head[v] = nullptr;
            }

            edge[cnt] = {&node[v], head[u]};
            head[u] = &edge[cnt++];

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Edge* begin(int x){
            return head[x];
        }
    };

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

        static int build_tree(int *son, Graph *graph){
            static int cnt = 1;
            int c = getchar(), now = cnt;
            while(c < '0' || '9' < c){
                c = getchar();
            }
            c -= '0';

            auto func = [&](){
                graph->add_edge(now, ++cnt);
                build_tree(son, graph);
            };

            switch(c){
                case 2:
                    son[now] = 2;
                    func();
                    func();
                    break;

                case 1:
                    son[now] = 1;
                    func();
                    break;

                case 0:
                    son[now] = 0;
                    break;

                default:
                    throw exception();
            }

            return cnt;
        }
    };

    static int num_of_son[N + 5];
    static Graph graph;

    Tools::build_tree(num_of_son, &graph);

    stack<int> st;
    st.push(1);

    static int mx[N + 5][3], mn[N + 5][3]; // 0->green 1->blue 2->red
    static bool vis[N + 5];
    while(!st.empty()){
        while(graph.begin(st.top()) != nullptr && !vis[graph.begin(st.top())->to->id]){
            st.push(graph.begin(st.top())->to->id);
        }
        if(num_of_son[st.top()] > 1 && !vis[graph.begin(st.top())->nxt->to->id]){
            st.push(graph.begin(st.top())->nxt->to->id);
        }else{
            switch (num_of_son[st.top()]) {
                case 2:
                    mx[st.top()][0] = max(mx[graph.begin(st.top())->to->id][1] + mx[graph.begin(st.top())->nxt->to->id][2],
                                          mx[graph.begin(st.top())->to->id][2] + mx[graph.begin(st.top())->nxt->to->id][1]) + 1;
                    mx[st.top()][1] = max(mx[graph.begin(st.top())->to->id][0] + mx[graph.begin(st.top())->nxt->to->id][2],
                                          mx[graph.begin(st.top())->to->id][2] + mx[graph.begin(st.top())->nxt->to->id][0]);
                    mx[st.top()][2] = max(mx[graph.begin(st.top())->to->id][0] + mx[graph.begin(st.top())->nxt->to->id][1],
                                          mx[graph.begin(st.top())->to->id][1] + mx[graph.begin(st.top())->nxt->to->id][0]);

                    mn[st.top()][0] = min(mn[graph.begin(st.top())->to->id][1] + mn[graph.begin(st.top())->nxt->to->id][2],
                                          mn[graph.begin(st.top())->to->id][2] + mn[graph.begin(st.top())->nxt->to->id][1]) + 1;
                    mn[st.top()][1] = min(mn[graph.begin(st.top())->to->id][0] + mn[graph.begin(st.top())->nxt->to->id][2],
                                          mn[graph.begin(st.top())->to->id][2] + mn[graph.begin(st.top())->nxt->to->id][0]);
                    mn[st.top()][2] = min(mn[graph.begin(st.top())->to->id][0] + mn[graph.begin(st.top())->nxt->to->id][1],
                                          mn[graph.begin(st.top())->to->id][1] + mn[graph.begin(st.top())->nxt->to->id][0]);
                    break;

                case 1:
                    mx[st.top()][0] = max(mx[graph.begin(st.top())->to->id][1], mx[graph.begin(st.top())->to->id][2]) + 1;
                    mx[st.top()][1] = max(mx[graph.begin(st.top())->to->id][0], mx[graph.begin(st.top())->to->id][2]);
                    mx[st.top()][2] = max(mx[graph.begin(st.top())->to->id][0], mx[graph.begin(st.top())->to->id][1]);

                    mn[st.top()][0] = min(mn[graph.begin(st.top())->to->id][1], mn[graph.begin(st.top())->to->id][2]) + 1;
                    mn[st.top()][1] = min(mn[graph.begin(st.top())->to->id][0], mn[graph.begin(st.top())->to->id][2]);
                    mn[st.top()][2] = min(mn[graph.begin(st.top())->to->id][0], mn[graph.begin(st.top())->to->id][1]);
                    break;

                case 0:
                    mx[st.top()][0] = 1;
                    mn[st.top()][0] = 1;
                    break;

                default:
                    throw exception();
            }
            vis[st.top()] = true;
            st.pop();
        }
    }

    printf("%d %d\n", max(mx[1][0], max(mx[1][1], mx[1][2])), min(mn[1][0], min(mn[1][1], mn[1][2])));
}