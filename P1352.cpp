//
// Created by kibi on 2021/8/6.
//
#include <bits/stdc++.h>
using namespace std;
int n,r[6005],dp[6005][2],a[6005];
vector<int> b[6005];
int f(int x){
    if(!b[x].size()){
        dp[x][0] = 0;
        dp[x][1] = r[x];
        return max(0,dp[x][1]);
    }
    dp[x][1] = r[x];
    for(int i = 0; i < b[x].size(); i++){
        dp[x][0] += f(b[x][i]);
        dp[x][1] += dp[b[x][i]][0];
    }
    return max(dp[x][0],dp[x][1]);
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> r[i];
    }
    for(int i = 1; i < n; i++){
        int l,t;
        cin >> l >> t;
        a[l] = t;
        b[t].push_back(l);
    }
    int root = -1;
    for(int i = 1; i <= n; i++){
        if(!a[i]){
            root = i;
            break;
        }
    }
    cout << f(root);

}

// 2023/8/16

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 6000;

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
            while ('0' <= c && c <= '9'){
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    class Graph{
        int cnt;
        class Node{
        public:
            int id, val;
        };
        class Edge{
        public:
            Node *to;
            Edge *nxt;
        };

        Edge *head[N + 5]{};
        Edge edge[N + 5]{};
        Node node[N + 5]{};

    public:
        Graph(int n, int *data){
            cnt = 0;
            for(int i = 1; i <= n; i++){
                node[i] = {i, data[i]};
                head[i] = nullptr;
            }
        }

        void add_edge(int u, int v, bool flag = false){
            edge[++cnt] = {&node[v], head[u]};
            head[u] = &edge[cnt];

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Edge* begin(int u){
            return head[u];
        }

        Node* get(int u){
            return &node[u];
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    static int r[N + 5];
    for(int i = 1; i <= n; i++){
        read(r[i]);
    }

    static Graph graph(n, r);

    static int in[N + 5];
    for(int i = 1; i < n; i++){
        int l, k;
        read(l), read(k);
        graph.add_edge(l, k);
        in[k]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++){
        in[i] ? void(0) : q.push(i);
    }

    int ans = 0;

    static int f[N + 5][2];
    while(!q.empty()){
        int u = q.front();
        q.pop();

        f[u][1] += graph.get(u)->val;
        ans = max(ans, max(f[u][1], f[u][0]));

        for(auto *i = graph.begin(u); i != nullptr; i = i->nxt){
            auto v = i->to;
            f[v->id][0] += max(f[u][1], f[u][0]);
            f[v->id][1] += f[u][0];
            in[v->id]--;
            if(!in[v->id]){
                q.push(v->id);
            }
        }
    }

    printf("%d\n", ans);


}
 *
 * */