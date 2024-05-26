//
// Created by kibi on 23-11-14.
//
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
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};
            flag ? add_edge(v, u) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    int n;
    read({&n});

    Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v;
        read({&u, &v});
        u--, v--;
        graph.add_edge(u, v, true);
    }


    bool col[n], ins[n];
    int rt = rand(n), x = 0, y = 0;
    memset(ins, 0, sizeof ins);

    stack<int> stk;
    stk.emplace(rt);
    col[rt] = false;
    ins[rt] = true;
    x++;
    while(!stk.empty()){
        int u = stk.top();
        ins[u] = true;
        stk.pop();
        for(auto i = graph.begin(u); i; i = i->nxt){
            if(ins[i->v]){
                continue;
            }
            col[i->v] = !col[u];
            col[i->v] ? y++ : x++;
            stk.emplace(i->v);
        }
    }

    int res[n];
    memset(res, 0, sizeof res);

    if(x > n / 3 && y > n / 3){
        int cnt_x = 1, cnt_y = 2;
        for(int i = 0; i < n; i++){
            if(!col[i] && cnt_x <= n){
                res[i] = cnt_x;
                cnt_x += 3;
            }else if(col[i] && cnt_y <= n){
                res[i] = cnt_y;
                cnt_y += 3;
            }
        }
        int cnt = 3;
        for(int i = 0; i < n; i++){
            if(!res[i]){
                res[i] = cnt;
                cnt += 3;
            }
        }
    }else if(x <= n / 3){
        int cnt = 3;
        bool vis[n];
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < n; i++){
            if(!col[i]){
                res[i] = cnt;
                vis[cnt - 1] = true;
                cnt += 3;
            }
        }
        cnt = 0;
        for(int i = 0; i < n; i++){
            if(!res[i]){
                while(vis[cnt]){
                    cnt++;
                }
                res[i] = ++cnt;
            }
        }
    }else if(y <= n / 3){
        int cnt = 3;
        bool vis[n];
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < n; i++){
            if(col[i]){
                res[i] = cnt;
                vis[cnt - 1] = true;
                cnt += 3;
            }
        }
        cnt = 0;
        for(int i = 0; i < n; i++){
            if(!res[i]){
                while(vis[cnt]){
                    cnt++;
                }
                res[i] = ++cnt;
            }
        }
    }

    for(auto &i : res){
        printf("%d ", i);
    }
    printf("\n");
}