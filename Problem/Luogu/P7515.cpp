//
// Created by kibi on 23-7-30.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 300, M = 300;

void read(int&);

int main(){

    class Graph{
        int head[N + M + 5], nxt[2 * N * M + 5], to[2 * N * M + 5], cnt;
        long long w[2 * N * M + 5];

    public:
        void add_edge(int u, int v, long long _w){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;
            w[cnt] = _w;
        }

        int begin(int x){
            return head[x];
        }

        int next(int x){
            return nxt[x];
        }

        int get(int x){
            return to[x];
        }

        long long get_w(int x){
            return w[x];
        }
    };

    int T;
    read(T);
    while(T--){
        int n, m;
        read(n), read(m);

        static int b[N + 5][M + 5];

        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                read(b[i][j]);
            }
        }

        static long long a[N + 5][M + 5];

        for(int i = n; i >= 1; i--){
            for(int j = m; j >= 1; j--){
                a[i][j] = b[i][j] - a[i+1][j] - a[i][j+1] - a[i+1][j+1];
            }
        }

        static Graph graph;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                long long mx = 1000000 - a[i][j], mn = -a[i][j];
                if(!((i+j)&1)){
                    graph.add_edge(j+n, i, mx);
                    graph.add_edge(i, j+n, -mn);
                }else{
                    graph.add_edge(j+n, i, -mn);
                    graph.add_edge(i, j+n, mx);
                }
            }
        }

        static bool inq[N + M + 5];
        static int tms[N + M + 5];
        static long long dis[N + M + 5];

        deque<int> q;
        bool flag = false;
        memset(dis, 0x3f, sizeof dis);

        dis[1] = 0;
        q.push_back(1);

        while(!q.empty()){
            int u = q.front();
            q.pop_front();
            ++tms[u];
            inq[u] = false;
            if(tms[u] > n + m){
                flag = true;
                break;
            }
            for(int i = graph.begin(u); i; i = graph.next(i)){
                int v = graph.get(i);
                long long w = graph.get_w(i);
                if(dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w;
                    if(!inq[v]){
                        if(!q.empty() && dis[v] < dis[q[0]]){
                            q.push_front(v);
                        }else{
                            q.push_back(v);
                        }
                        inq[v] = true;
                    }
                }
            }
        }

        if(flag){
            printf("NO\n");
        }else{
            printf("YES\n");
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    if((i + j) & 1){
                        a[i][j] -= dis[i];
                        a[i][j] += dis[j+n];
                    }else{
                        a[i][j] += dis[i];
                        a[i][j] -= dis[j+n];
                    }
                    printf("%lld ", a[i][j]);
                }
                printf("\n");
            }
        }

        if(!T){
            continue;
        }
        memset(inq, 0, sizeof inq);
        memset(tms, 0, sizeof tms);
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        graph = Graph();
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
    x =  s * w;
}