//
// Created by kibi on 23-9-10.
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
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };
        Edge *head[N + 5];
        Edge edge[2 * N + 5];
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

    static int n, m;
    read(n), read(m);

    static Graph graph;
    static bool rt[N + 5];
    for(int i = 1; i <= n; i++){
        int fa;
        read(fa);
        if(fa == -1 || fa == i){
            rt[i] = true;
            continue;
        }
        graph.add_edge(fa, i);
    }

    static int raw_data[N + 5];
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
    }

    static int ans = 1e9;

    class Work{

        class Data{
        public:
            Data(int val, int num):val(val), num(num){}

            int val, num;
            class Cmp{
            public:
                bool operator () (const Data &a, const Data &b){
                    return a.val > b.val;
                }
            };
        };

        void deal(priority_queue<Data, vector<Data>, Data::Cmp> &q, int val, bool flag = true){
            Data temp_data = q.top();
            q.pop();
            int num = temp_data.num + flag;
            long long sum = (long long)temp_data.val * temp_data.num + val;
            int avg = (int)(sum / num);
            while(!q.empty() && avg > q.top().val){
                temp_data = q.top();
                q.pop();
                num += temp_data.num;
                sum += (long long)temp_data.num * temp_data.val;
                avg = (int)(sum / num);
            }
            int rest = (int)(sum - (long long)avg * num);
            if(rest) {
                q.emplace(avg + 1, rest);
            }
            q.emplace(avg, num - rest);
        }

        priority_queue<Data, vector<Data>, Data::Cmp> dfs(int u){
            priority_queue<Data, vector<Data>, Data::Cmp> q, tem;

            for(auto i = graph.head[u]; i; i = i->nxt){
                tem = dfs(i->v);
                while(!tem.empty()){
                    q.push(tem.top());
                    tem.pop();
                }
            }

            if(!q.empty() && raw_data[u] > q.top().val){
                deal(q, raw_data[u]);
            }else if(q.empty() || raw_data[u] < q.top().val){
                q.emplace(raw_data[u], 1);
            }else{
                Data temp_data = q.top();
                q.pop();
                temp_data.num++;
                q.emplace(temp_data);
            }

            return q;
        }

    public:
        Work(){
            bool flag = false;

            priority_queue<Data, vector<Data>, Data::Cmp> q, tem;
            for(int i = 1; i <= n; i++){
                if(rt[i]){
                    tem = dfs(i);
                    while(!tem.empty()){
                        q.push(tem.top());
                        tem.pop();
                    }
                    flag = true;
                }
            }

            if(!flag){
                long long sum = 0;
                for(int i = 1; i <= n; i++){
                    sum += raw_data[i];
                }
                sum += m;
                sum /= n;
                ans = (int)sum;
                return;
            }

            deal(q, m, false);

            ans = q.top().val;
        }
    };

    Work();

    printf("%d\n", ans);

}