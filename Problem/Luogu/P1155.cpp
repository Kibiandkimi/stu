//
// Created by kibi on 23-7-27.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

void read(int&);

int main(){

    class Graph
    {
        int head[N + 5], nxt[2*N*N+5], to[2*N*N+5], cnt;

    public:
        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;

        }

        bool vis[N + 5], col[N + 5];
        bool discolor(int n){
            queue<int> q;
            for(int i = 1; i <= n; i++){
                if(!vis[i]){
                    vis[i] = true;
                    q.push(i);
                }
                while(!q.empty()){
                    int u = q.front();
                    q.pop();
                    for(int j = head[u]; j; j = nxt[j]){
                        if(!vis[to[j]]){
                            vis[to[j]] = true;
                            col[to[j]] = !col[u];
                            q.push(to[j]);
                        }else if(col[to[j]] == col[u]){
                            return false;
                        }
                    }
                }
            }
            return true;
        }

    };

    class DoubleStack{
        int n;

        int st[2][N + 5]{}, l[2]{}, r[2]{};

        int cnt;
        //        int **res;

    public:

        int ans[2*N + 5]{};
        bool flag;

        explicit DoubleStack(int n) {
            this -> n = n;
            l[0] = l[1] = 0;
            r[0] = r[1] = -1;
            cnt = 0;
            //			*res = ans;
            flag = false;
        }

        void push(int x, bool id){

            int *_st = st[id], &_l = l[id], &_r = r[id];

            if(!id){
                while(pop(false));
            }
            while( _l <= _r && _st[_r] < x){
                if(!pop(id)){
                    pop(!id);
                }
            }
            if(id){
                while(pop(false));
            }
            _st[++_r] = x;
            ans[++cnt] = id ? 3 : 1;
        }

        bool pop(bool id){
            static int pos = 1;
            int *_st = st[id], &_l = l[id], &_r = r[id];
            if( _l <= _r && _st[_r] == pos){
                ans[++cnt] = id ? 4 : 2;
                _r--;
                ++pos;
                if(pos > n){
                    flag = true;
                }
                return true;
            }
            return false;
        }
    };

    static Graph graph;

    static int p[N + 5], mnv[N + 5];
    int n;

    read(n);
    for(int i = 1; i <= n; i++){
        read(p[i]);
    }

    mnv[n+1] = 1e9;
    mnv[n] = p[n];
    for(int i = n-1; i >= 1; i--){
        mnv[i] = min(mnv[i+1], p[i]);
    }

    for(int i = 1; i <= n; i++){
        for(int j = i+1; j <= n; j++){
            if(mnv[j+1] < p[i] && p[i] < p[j]){
                graph.add_edge(i, j);
            }
        }
    }

    bool res = graph.discolor(n);

    if(!res){
        printf("0\n");
        return 0;
    }

    static DoubleStack stk(n);

    for(int i = 1; i <= n; i++){
        stk.push(p[i], graph.col[i]);
    }

    // bool flag = true;

    while(!stk.flag){
        // flag = false;
        while(stk.pop(false));
        while(stk.pop(true));
    }

    for(int i = 1; i <= 2*n; i++){
        char s = stk.ans[i] == 1 ? 'a' : stk.ans[i] == 2 ? 'b' : stk.ans[i] == 3 ? 'c' : 'd';
        printf("%c ", s);
    }

}

void read(int &x){
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