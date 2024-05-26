//
// Created by kibi on 2022/8/27.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c=='-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

int b[250005], sb[250005]/*, mx[250005]*/;
int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

struct Edge{
    explicit Edge(int tu = 0, int tv = 0, int tw = 1e9){
        u = tu, v = tv, w = tw;
    }
    void get(int &tu, int &tv, int&tw)const{
        tu = u, tv = v, tw = w;
    }
    int u, v, w;
}edge[1000005];
int cnt;
bool cmp(Edge a, Edge b){
    return a.w < b.w;
}

int main(){
    int n, h[505][505];
    read(n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            read(h[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int u = (i-1)*n+j;
            b[u] = u, sb[u] = 1/*, mx[u] = h[i][j]*/;
            int v[4] = {i!=1?u-n:-1, i!=n?u+n:-1, j!=1?u-1:-1, j!=n?u+1:-1};
            for(int k : v){
                if(k < 0){
                    continue;
                }
                int vv = k;
                edge[cnt++] = Edge(u, vv, fabs(h[(vv-1)/n+1][(vv-1)%n+1]-h[i][j]));
            }
        }
    }
    sort(edge, edge+cnt, cmp);
    int s = n*n;
    for(int i = 0; i < cnt; i++){
        int u, v, w;
        edge[i].get(u, v, w);
        if(find(u) != find(v)){
            sb[b[v]] += sb[b[u]];
            if(sb[b[v]] >= s/2+s%2){
                printf("%d", w);
                return 0;
            }
            b[b[u]] = b[b[v]];
        }
    }
}