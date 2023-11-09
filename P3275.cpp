//
// Created by kibi on 2021/8/20.
//

// TLE with new hack data

#include <bits/stdc++.h>
using namespace std;
int n,m;
long long s[100005],vis[100005],ss[100005];
vector<pair<int, int> > a[100005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int x,u,v;
        scanf("%d %d %d", &x, &u, &v);
        switch(x){
            // case 1:a[u].emplace_back(make_pair(v, 0));a[v].emplace_back(make_pair(u, 0));break;
            // case 2:a[v].emplace_back(make_pair(u, -1));break;
            // case 3:a[u].emplace_back(make_pair(v, 0));break;
            // case 4:a[u].emplace_back(make_pair(v, -1));break;
            // case 5:a[v].emplace_back(make_pair(u, 0));break;
            case 1:a[u].emplace_back(make_pair(v, 0));a[v].emplace_back(make_pair(u, 0));break;
            case 2:a[u].emplace_back(make_pair(v, 1));break;
            case 3:a[v].emplace_back(make_pair(u, 0));break;
            case 4:a[v].emplace_back(make_pair(u, 1));break;
            case 5:a[u].emplace_back(make_pair(v, 0));break;
        }
        if(x%2==0&&u==v){
            cout << -1;
            return 0;
        }
    }
    // for(int i = 1; i <= n; i++){
    //     s[i] = 1e10;
    // }
    // for(int i = n; i > 0; i--){
    //     a[0].emplace_back(make_pair(i, 1));
    // }
    for(int i = 1; i <= n; i++){
        a[0].emplace_back(make_pair(i, 1));
    }
    vis[0] = 1;
    queue<int> q;
    q.push(0);
    bool flag = true;
    while(!q.empty()){
        int t = q.front();
        q.pop();
        ss[t]++;
        if(ss[t]>n){
            flag = false;
            break;
        }
        vis[t] = 0;
        for(int i = 0, sa = a[t].size(); i < sa; i++){
            if(s[a[t][i].first]<s[t]+a[t][i].second){
                s[a[t][i].first] = s[t]+a[t][i].second;
                if(!vis[a[t][i].first]){
                    q.push(a[t][i].first);
                    vis[a[t][i].first] = 1;
                }
            }
        }
    }
    if(!flag){
        cout << -1;
    }else{
        long long ss = 0;
        long long mn = 1e10;
        // for(int i = 1; i <= n; i++)mn = min(mn, s[i]);
        // mn--;
        // for(int i = 1; i <= n; i++)ss+=s[i]-mn;
        for(int i = 1; i <= n; i++)ss+=s[i];
        printf("%lld", ss);
    }
}

// 23-11-8

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

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

    auto rand = [](int val){
        return (int)((rnd() % val + val) % val);
    };

    class Graph{
        class Edge{
        public:
            int v, w;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};
            flag ? add_edge(v, u, w) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, col;
            bool vis;
        };

        class Ret{
        public:
            int num;
            vector<Node> *node;
            vector<int> *sum;
        };

        int num;
        Node *rt;
        Graph *graph;
        vector<Node> node;
        vector<int> sum;

        void dfs(Node *u){
            static int cnt;
            static stack<int> stk;
            u->dfn = u->low = ++cnt;
            u->vis = true;
            stk.push(u->id);

            for (auto i = graph->begin(u->id); i; i = i->nxt) {
                Node *v = &node[i->v];
                if (!v->dfn) {
                    dfs(v);
                    u->low = min(u->low, v->low);
                } else if(v->vis) {
                    u->low = min(u->low, v->dfn);
                }
            }

            if(u->dfn == u->low){
                int x;
                sum.emplace_back(0);
                do {
                    x = stk.top();
                    stk.pop();
                    node[x].vis = false;
                    node[x].col = num;
                    sum.back()++;
                } while(x != u->id);
                num++;
            }
        }

    public:
        Tarjan(int n, int rt, Graph *graph):num(0), graph(graph), node(n){
            for(int i = 0; i < n; i++){
                node[i].id = i, node[i].vis = false;
            }

            this->rt = &node[rt];

            dfs(this->rt);

            for(auto &i : node){
                if(!i.dfn){
                    dfs(&i);
                }
            }
        }

        Ret get(){
            return {num, &node, &sum};
        }
    };

    int n, k;
    read({&n, &k});

    Graph graph(n);

    for(int i = 0; i < k; i++){
        int x, u, v;
        read({&x, &u, &v});
        u--, v--;
        switch(x){
            case 1:
                graph.add_edge(u, v, 0, true);
                break;
            case 2:
                graph.add_edge(u, v, 1);
                break;
            case 3:
                graph.add_edge(v, u, 0);
                break;
            case 4:
                graph.add_edge(v, u, 1);
                break;
            case 5:
                graph.add_edge(u, v, 0);
                break;
            default:
                throw exception();
        }
    }

    Tarjan tarjan(n, rand(n), &graph);
    auto ret = tarjan.get();
    auto node = ret.node;
    auto num = ret.num;
    auto sum_num = ret.sum;

    int in[num];
    memset(in, 0, sizeof in);

    Graph new_graph(num);

    for (int i = 0; i < n; ++i) {
        for (auto j = graph.begin(i); j; j = j->nxt){
            if((*node)[i].col == (*node)[j->v].col && j->w == 1){
                printf("-1\n");
                return 0;
            }else if((*node)[i].col != (*node)[j->v].col){
                in[(*node)[j->v].col]++;
                new_graph.add_edge((*node)[i].col, (*node)[j->v].col, j->w);
            }
        }
    }

    int dis[num];
    queue<int> q;
    for(int i = 0; i < num; i++){
        if(!in[i]){
            q.push(i);
        }
        dis[i] = 1;
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto i = new_graph.begin(u); i; i = i->nxt){
            int v = i->v;
            dis[v] = max(dis[v], dis[u] + i->w);
            in[v]--;
            if(!in[v]){
                q.push(v);
            }
        }
    }
    long long res = 0;
    for(int i = 0; i < num; i++){
        res += (long long)dis[i] * (*sum_num)[i];
    }
    printf("%lld\n", res);
}
 *
 * */