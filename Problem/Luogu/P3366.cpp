//
// Created by kibi on 2021/8/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,b[5005];
struct node{
    int u,v,w;
};
node a[200005];
int cmp(node a, node b){
    return a.w < b.w;
}
int find(int x){
    if(b[x]!=x)b[x]=find(b[x]);
    return b[x];
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[i] = node({u,v,w});
    }
    sort(a+1,a+1+m,cmp);
    int w = 0;
    for(int i = 1; i <= m; i++){
        if(find(a[i].u)!=find(a[i].v)){
            b[find(a[i].u)] = find(a[i].v);
            w += a[i].w;
        }
    }
    int t = find(1);
    for(int i = 1; i <= n; i++){
        if(find(i) != t){
            cout << "orz";
            return 0;
        }
    }
    cout << w;
    return 0;
}

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 5000, M = 200000;

void read(int&);
int read();

int main(){
    
    class Edge{
    public:
        int u, v, w;
        static bool cmp(Edge a, Edge b){
            return a.w < b.w;
        }
    };

    class Bcj{
    public:
        int id;
        Bcj *fa;

        Bcj* find(){
            if(fa != this){
                fa = fa->find();
            }
            return fa;
        }

        Bcj(){
            fa = this;
        }
    };

    static Edge edge[M+5];

    int n, m;
    read(n), read(m);

    for(int i = 1; i <= m; i++){
        edge[i] = {read(), read(), read()};
    }

    sort(edge+1, edge+1+m, Edge::cmp);

    static Bcj bcj[N + 5];

    for(int i = 1; i <= n; i++){
        bcj[i].id = i;
    }

    int ans = 0, num = 0;

    for(int i = 1; i <= m; i++){
        static int u, v;
        u = edge[i].u, v = edge[i].v;
        if(bcj[u].find() != bcj[v].find()){
            *bcj[u].fa = bcj[v];
            ans += edge[i].w;
            if(++num == n-1){
                break;
            }
        }
    }

    if(num == n-1){
        printf("%d\n", ans);
    }else{
        printf("orz\n");
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

int read(){
    int x;
    read(x);
    return x;
}

*/