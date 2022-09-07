//
// Created by kibi on 22-9-7.
//
#include <bits/stdc++.h>
using namespace std;
int n;
double xy[25][2];
vector<double> g[25];
//struct Edge{
//    Edge(int u, int v, double w){
//        this->u = u, this->v = v, this->w = w;
//    }
//    int u, v;
//    double w;
//};
//vector<Edge> edge;
int b[25];

void read(int &x);
int find(int x);
//bool cmp(Edge a, Edge b);

int main(){
    read(n);
    xy[0][0] = 0, xy[0][1] = 0;
    for(int i = 1; i <= n; i++){
        //        b[i] = i;
        //        read(xy[i][0]), read(xy[i][1]);
        g[i].resize(n+4);
        scanf("%lf %lf", &xy[i][0], &xy[i][1]);
    }
    g[0].resize(n+4);
    for(int i = 0; i <= n; i++){
        //        g[i].resize(n+4);
        for(int j = i+1; j <= n; j++){
            //            edge.emplace_back(i, j, sqrt(pow(xy[i][0]-xy[j][0], 2)+pow(xy[i][1]-xy[j][1], 2)));
            g[i][j] = sqrt(pow(xy[i][0]-xy[j][0], 2)+pow(xy[i][1]-xy[j][1], 2));
            g[j][i] = g[i][j];
        }
    }
    double d[20][34005];
    memset(d, 0x43, sizeof d);
    double ans = d[0][0];
    for(int i = 1; i <= n; i++){
        d[i][1<<(i-1)] = g[0][i];
    }
    for(int k = 1; k < (1<<n); k++){
        for(int i = 1; i <= n; i++){
            if((k&(1<<(i-1)))==0){
                continue;
            }
            for(int j = 1; j <= n; j++){
                if(i == j){
                    continue;
                }
                if((k&(1<<(j-1)))==0){
                    continue;
                }
                d[i][k] = min(d[i][k], d[j][k-(1<<(i-1))]+g[i][j]);
            }
        }
    }
    for(int i = 1; i <= n; i++){
        ans = min(d[i][(1<<n)-1], ans);
    }
    printf("%.2lf", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
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

//int find(int x){
//    if(x != b[x]){
//        return b[x] = find(b[x]);
//    }
//    return x;
//}

//bool cmp(Edge a, Edge b){
//    return a.w<b.w;
//}