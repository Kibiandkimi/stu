//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c;
int w[1005][1005];
long long v[1005][1005][3];
int t[4][2] = {{1,0},{-1, 0}, {0, 1}, {0, -1}};
bool vis[1005][1005];
struct node{
    int x, y;
    long long v;
    bool operator <(const node &b) const{
        return v > b.v;
    }
};
//vector<node> g[1005];

long long dis[1005][1005];

//void f(int x, int y, int d){
//    vis[x][y] = true;
//    for(int i = 0; i <= 3; i++){
//        int fx = x+t[i][0], fy = y+t[i][y];
//        if(!vis[fx][fy]){
//            f(fx, fy, d);
//        }
//    }
//}

void f(int x, int y){
    memset(dis, 0x3f, sizeof dis);
    //    memset(res, 0, sizeof res);
    memset(vis, 0, sizeof vis);

    priority_queue<node> q;

    q.push({x, y, w[x][y]});

    dis[x][y] = w[x][y];

    while(!q.empty()){
        node u = q.top();
        q.pop();
        if(vis[u.x][u.y]){
            continue;
        }
        vis[u.x][u.y] = true;
        for(int i = 0; i < 4; i++){
            int fx = u.x+t[i][0], fy = u.y+t[i][1];
            if(fx<1||fx>n||fy<1||fy>m){
                continue;
            }
            if(dis[fx][fy]>dis[u.x][u.y]+w[fx][fy]){
                dis[fx][fy] = dis[u.x][u.y] + w[fx][fy];
                q.push({fx, fy, dis[fx][fy]});
            }
        }
    }

}

int main(){
    scanf("%d %d %d %d %d", &n, &m, &a, &b, &c);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &w[i][j]);
        }
    }

    f(1, a);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][0] = dis[i][j];
        }
    }

    f(n, b);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][1] = dis[i][j];
        }
    }

    f(n, c);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][2] = dis[i][j];
        }
    }

    long long ans = 1e18;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans = min(ans, v[i][j][0] + v[i][j][1] + v[i][j][2] - 2*w[i][j]);
        }
    }
    printf("%lld", ans);

}

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 1000, M = 1000;
const int F[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void read(int&);

int main(){

    class Node{
    public:
        long long w;
        int x, y;

        Node(long long w, int x, int y){
            this -> w = w,
            this -> x = x,
            this -> y = y;
        }

        class Cmp {
        public:
            bool operator() (Node a, Node b) {
                return a.w > b.w;
            }
        };
    };

    int n, m, a, b, c;
    read(n), read(m), read(a), read(b), read(c);

    static int graph[N + 5][M + 5];

    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= m; j++){
            read(graph[i][j]);
        }
    }

    static long long f[N + 5][M + 5][3], sum[N + 5][M + 5]; // 0:light 1:red-house 2:bamboo-forest

    memset(f, 0x3f, sizeof f);

    for(int id = 0; id < 3; id++){

        static const int begin[3][2] = {{n, a}, {1, b}, {1, c}};
        static bool in[N + 5][M + 5];

        memset(in, 0, sizeof in);

        priority_queue<Node, vector<Node>, Node::Cmp> q;
        auto [tem_x, tem_y] = begin[id];
        q.emplace(f[tem_x][tem_y][id], tem_x, tem_y);

        f[tem_x][tem_y][id] = graph[tem_x][tem_y];
        while(!q.empty()){
            auto u = q.top();
            q.pop();
            auto [ignore, x, y] = u;

            if(in[x][y]){
                continue;
            }
            in[x][y] = true;

            for(auto i : F){
                int _x = x + i[0], _y = y + i[1];
                if(!(0 < _x && _x <= n && 0 < _y && _y <= m)){
                    continue;
                }
                long long w = f[x][y][id] + graph[_x][_y];
                if(f[_x][_y][id] > w && !in[_x][_y]){
                    f[_x][_y][id] = w;
                    q.emplace(f[_x][_y][id], _x, _y);
                }
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                sum[i][j] += f[i][j][id];
            }
        }
    }

    long long ans = sum[1][1] - 2*graph[1][1];

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans = min(ans, sum[i][j] - 2*graph[i][j]);
        }
    }

    printf("%lld\n", ans);
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

*/

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 1000, M = 1000;
const int F[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void read(int&);

int main(){

    class Node{
    public:
        long long w;
        int x, y;

        Node(long long w, int x, int y){
            this -> w = w,
            this -> x = x,
            this -> y = y;
        }

        class Cmp {
        public:
            bool operator() (Node a, Node b) {
                return a.w > b.w;
            }
        };
    };

    int n, m, a, b, c;
    read(n), read(m), read(a), read(b), read(c);

    static int graph[N + 5][M + 5];

    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= m; j++){
            read(graph[i][j]);
        }
    }

    static long long f[N + 5][M + 5][3], sum[N + 5][M + 5]; // 0:light 1:red-house 2:bamboo-forest

    memset(f, 0x3f, sizeof f);

    for(int id = 0; id < 3; id++){

        static const int begin[3][2] = {{n, a}, {1, b}, {1, c}};
        static bool in[N + 5][M + 5];

        memset(in, 0, sizeof in);

        priority_queue<Node, vector<Node>, Node::Cmp> q;
        auto [tem_x, tem_y] = begin[id];
        q.emplace(f[tem_x][tem_y][id], tem_x, tem_y);

        f[tem_x][tem_y][id] = graph[tem_x][tem_y];
        while(!q.empty()){
            auto u = q.top();
            q.pop();
            auto [ignore, x, y] = u;

            if(in[x][y]){
                continue;
            }
            in[x][y] = true;

            for(auto i : F){
                int _x = x + i[0], _y = y + i[1];
                if(!(0 < _x && _x <= n && 0 < _y && _y <= m)){
                    continue;
                }
                long long w = f[x][y][id] + graph[_x][_y];
                if(f[_x][_y][id] > w && !in[_x][_y]){
                    f[_x][_y][id] = w;
                    q.emplace(f[_x][_y][id], _x, _y);
                }
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                sum[i][j] += f[i][j][id];
            }
        }
    }

    long long ans = sum[1][1] - 2*graph[1][1];

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans = min(ans, sum[i][j] - 2*graph[i][j]);
        }
    }

    printf("%lld\n", ans);
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

*/