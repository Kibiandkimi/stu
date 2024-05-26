//
// Created by Lenovo on 24-4-16.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c){
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
            int v;
            Edge *nxt;
        };

        std::vector<Edge*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};
            return flag ? add_edge(v, u) : void();
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    int n;
    read(n);

    Graph g1(n), g2(n); // g1->ordinary, g2->-g1
    int val[n], in[n];
    long long ans = 0, f[n][2];
    memset(in, 0, sizeof in);
    for(int i = 0; i < n; i++){
        int v;
        read(val[i]), read(v);
        --v;
        g1.add_edge(i, v);
        g2.add_edge(v, i);
        in[v]++;
        f[i][0] = 0, f[i][1] = val[i];
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(!in[i]){
            q.emplace(i);
        }
    }

    while(!q.empty()){
        static int now;
        static long long sum1, sum0;
        now = q.front(), sum1 = 0, sum0 = 0;
        q.pop();

        for(auto i = g2.begin(now); i; i = i->nxt){
            sum1 += max(f[i->v][0], f[i->v][1]);
            sum0 += f[i->v][0];
        }

        f[now][0] = sum1, f[now][1] = sum0 + val[now];
        auto nxt = g1.begin(now);
        if(nxt != nullptr) {
            in[nxt->v]--;
            if(!in[nxt->v]){
                q.emplace(nxt->v);
            }
        }else{
            ans += max(f[now][0], f[now][1]);
        }
    }

    for(int i = 0; i < n; i++){
        if(in[i]){
            static long long sum1, sum0, res;
            static int pre;
            sum1 = sum0 = 0;
            for(auto j = g2.begin(i); j; j = j->nxt){
                if(in[j->v]){
                    pre = j->v;
                    continue;
                }
                sum1 += max(f[j->v][0], f[j->v][1]);
                sum0 += f[j->v][0];
            }

            in[i]--;
            f[i][0] = sum1, f[i][1] = sum0 + val[i];
            auto tem1 = f[i][1]/*, tem2 = f[pre][0]*/;
            f[i][1] = f[i][0];

            for(auto j = g1.begin(i); j->v != i; j = g1.begin(j->v)){
                sum1 = sum0 = 0;
                for(auto k = g2.begin(j->v); k; k = k->nxt){
                    sum1 += max(f[k->v][0], f[k->v][1]);
                    sum0 += f[k->v][0];
                }
                f[j->v][0] = sum1, f[j->v][1] = sum0 + val[j->v];
                in[j->v]--;
            }

            res = max(f[pre][0], f[pre][1]);

            f[i][1] = tem1;

            for(auto j = g1.begin(i); j->v != i; j = g1.begin(j->v)){
                sum1 = sum0 = 0;
                for(auto k = g2.begin(j->v); k; k = k->nxt){
                    sum1 += max(f[k->v][0], f[k->v][1]);
                    sum0 += f[k->v][0];
                }
                f[j->v][0] = sum1, f[j->v][1] = sum0 + val[j->v];
            }

            res = max({res, f[pre][0], f[pre][1] - val[pre]});
            ans += res;
        }
    }

    printf("%lld\n", ans);
}