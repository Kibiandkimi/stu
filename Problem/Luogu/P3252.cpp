//
// Created by kibi on 23-9-10.
//

// best solution (23-9-10) 62ms

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 100000;

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
            int v;
            Edge *nxt;
        };

        Edge *head[N + 5];
        Edge edge[N + 5];
        int cnt;

        friend class Work;

    public:
        void add_edge(int u, int v, bool flag = false){
            edge[++cnt] = {v, head[u]};
            head[u] = &edge[cnt];

            if(!flag){
                return;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    static int n, s;
    read(n), read(s);

    static int val[N + 5];
    for(int i = 1; i <= n; i++){
        read(val[i]);
    }

    static Graph graph;
    static bool not_rt[N + 5];
    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v);
        not_rt[v] = true;
    }

    class Que{
        int data[N + 5], sum[N + 5], l, r;

    public:
        Que():l(0), r(-1){}

        void push(int v){
            data[++r] = v;
            sum[r] = sum[r - 1] + v;
        }

        void pop_front(){
            // sum -= data[l++];
            l++;
        }

        void undo_pop_front(){
            // sum += data[--l];
            --l;
        }

        void pop_back(){
            // sum -= data[r--];
            r--;
        }

        int get_sum() const {
            return sum[r] - sum[l - 1];
        }

        int get_l() const {
            return l;
        }

        int get_r() const {
            return r;
        }

        void set(int _l, int _r){
            l = _l, r = _r;
        }

    };

    static int pos_l[N + 5], pos_r[N + 5], ans;
    // static int que[N + 5];

    static Que que;

    class Work{
    public:
        explicit Work(int u){
            que.push(val[u]);

            while(que.get_sum() > s){
                que.pop_front();
            }

            if(que.get_sum() == s){
                ans++;
            }

            pos_l[u] = que.get_l();
            pos_r[u] = que.get_r();

            for(auto i = graph.head[u]; i; i = i->nxt){
                Work(i->v);
                que.set(pos_l[u], pos_r[u]);
            }
        }
    };

    for(int i = 1; i <= n; i++){
        if(!not_rt[i]){
            Work{i};
            break;
        }
    }

    printf("%d\n", ans);
}