#include <bits/stdc++.h>
using namespace std;

const int Size = 10005;
class Graph {
    int head[Size], nxt[Size], to[Size], tot;

public:
    void addEdge(int u, int v, bool flag = true) {
        to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
        if (!flag) {
            return;
        }
        to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
    }
    int begin(int x) {
        return head[x];
    }
    int next(int x) {
        return nxt[x];
    }
    int get(int x) {
        return to[x];
    }
};

void read(int &x);

//int vis[Size];
static Graph g;
//bool f(int u, int fa){
//    vis[u] = true;
//    for(int i = g.begin(u); i; i = g.next(i)){
//        static int v;
//        v = g.get(i);
//        if(v != fa){
//            if(vis[v]){
//                return true;
//            }else{
//                return f(v, u);
//            }
//        }
//    }
//    return false;
//}

int main(){
    int n, m;

    read(n), read(m);
    for(int i = 0; i < m; ++i){
        int u, v;
        read(u), read(v);
        g.addEdge(u, v);
    }
//    int sum = 0;
//    for(int i = 1; i <= n; i++){
//        if(!vis[i]){
//            sum += 2*f(i, 0);
//            sum++;
//        }
//    }
//    sum--;
//    printf("%d", sum);
    printf("%d", (n-1)-m);
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