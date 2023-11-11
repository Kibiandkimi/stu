//
// Created by kibi on 23-11-9.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](initializer_list<int*> x){
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

        for(auto &i : x){
            read(*i);
        }
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;
        map<int, int> mp;

    public:
        void add_edge(int u, int v, bool flag = false){
            if(mp.find(u) == mp.end()){
                mp[u] = (int)head.size();
                head.emplace_back(nullptr);
            }
            head[mp[u]] = new Edge{v, head[mp[u]]};
            flag ? add_edge(v, u) : void(0);
        }

        Edge* begin(int u){
            return mp.find(u) == mp.end() ? nullptr : head[mp[u]];
        }
        /*
        ~Graph(){
            for(auto &i : head){

            }
        }
*/
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, col;
            bool vis;
            Node(int id, int dfn, int low, int col, bool vis):id(id), dfn(dfn), low(low), col(col), vis(vis){}
        };

        int cnt_col;
        Node *rt;
        Graph *graph;
        //        vector<Node*> node;
        map<int, Node*> mp;

        void dfs(Node *u){
            static int cnt;
            static stack<int> stk;
            u->dfn = u->low = ++cnt, u->vis = true;
            stk.emplace(u->id);
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                if(mp.find(i->v) == mp.end()){
                    mp[i->v] = new Node{i->v, 0, 0, 0, false};
                    /*                    mp[i->v] = (int)node.size();
                    node.emplace_back(new Node{i->v, 0, 0, 0, false});*/
                }
                if(!mp[i->v]->dfn){
                    dfs(mp[i->v]);
                    u->low = min(u->low, mp[i->v]->low);
                }else if(mp[i->v]->vis){
                    u->low = min(u->low, mp[i->v]->dfn);
                }
            }
            if(u->dfn == u->low){
                int x;
                do {
                    x = stk.top();
                    stk.pop();
                    mp[x]->vis = false;
                    mp[x]->col = cnt_col;
                } while(x != u->id);
                cnt_col++;
            }
        }

    public:
        Tarjan(int rt, Graph *graph):graph(graph), cnt_col(0){
            mp[rt] = new Node{rt, 0, 0, 0, false};
            /*            mp[rt] = (int)node.size();
            node.emplace_back(new Node{rt, 0, 0, 0, false});*/
            this->rt = mp[rt];
            dfs(this->rt);
        }

        Node* get_node(int u){
            return mp[u];
            //            return node[mp[u]];
        }

        friend class Work;
    };

    int T;
    read({&T});

    while(T--){
        static int n;
        int mxw = 0;
        set<int> ste, stw;
        read({&n});
        int w[n], e[n];
        for(auto &i : w){
            read({&i});
            stw.insert(i);
            mxw = max(mxw, i);
        }
        for(auto &i : e){
            read({&i});
            ste.insert(i);
        }
        ste.insert(1);

        Graph graph;
        for(int i = 0; i < n; i++){
            graph.add_edge(w[i], e[i]);
        }

        for(auto &i : ste){
            for(int j = 1; i * j <= mxw; j++){
                if(stw.find(i * j) != stw.end()){
                    graph.add_edge(i, i * j);
                }
            }
        }

        Tarjan tarjan(1, &graph);

        class Work{
        public:
            Work(Tarjan *tarjan, int *w, int *e){
                int ans = 0;
                for(int i = 0; i < n; i++){
                    if(tarjan->get_node(w[i])->col == tarjan->get_node(e[i])->col){
                        ans++;
                    }
                }
                printf("%d\n", ans);
            }
        };

        Work{&tarjan, w, e};
    }
}