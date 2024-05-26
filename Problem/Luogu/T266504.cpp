//
// Created by kibi on 22-8-28.
//
//60pts
//TODO hack 3 1\n 9 0 3\n 0 3 3\n 3 3 0\n 1 1 1 1 100\n
#include <bits/stdc++.h>
using namespace std;
int n, m, a[505][505];
long long s[505][505], cf[505][505];

bool getBoolean(int c) { return c < '0' || '9' < c; }

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getBoolean(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getBoolean(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

struct node{
    node(int tx, int ty){
        x = tx, y = ty;
    }
    int x, y;
};
bool vis[505][505], vis2[505][505];
//int l = 0, r = -1;

void update(queue<node> &q, int x, int y, int vx, int vy) {
    if(s[vx][vy] > s[x][y] + 1){
        long long c = min(s[vx][vy] - a[vx][vy], s[vx][vy] - (s[x][y] + 1));
        if(c > 0){
            s[vx][vy] -= c;
            if(!vis[vx][vy]) {
                vis[vx][vy] = true;
                q.emplace(vx, vy);
            }
        }
    }
    if(s[vx][vy] > s[x][y] && !vis2[vx][vy]){
        q.emplace(vx, vy);
        vis2[vx][vy] = true;
    }
}

int main(){
    read(n);
    read(m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            read(a[i][j]);
        }
    }

    for(int i = 1; i <= m; i++){
        int x1, y1, x2, y2, k;
        read(x1);
        read(y1);
        read(x2);
        read(y2);
        read(k);
        cf[x1][y1]+=k;
        cf[x2+1][y1]-=k;
        cf[x1][y2+1]-=k;
        cf[x2+1][y2+1]+=k;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cf[i][j] = cf[i-1][j]+cf[i][j-1]-cf[i-1][j-1]+cf[i][j];
            s[i][j] = cf[i][j]+a[i][j];
//            s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+cf[i][j]+a[i][j];
        }
    }

    s[n][n] = -1e9;
    vis2[n][n] = true;
    queue<node> q;
    q.emplace(n, n);
//    q.emplace(n, n);
//    for(int i = n; i >= 1; i--){
//        for(int j = n; j >= 1; j--){
//            q.emplace(i, j);
//            vis[i][j] = true;
//        }
//    }
    while(!q.empty()){
        node u = q.front();
        q.pop();
        int x = u.x, y = u.y;
        vis[x][y] = false;
        if(x != 1){
            update(q, x, y, x - 1, y);
        }
        if(x != n){
            update(q, x, y, x+1, y);
        }
        if(y != 1){
            update(q, x, y, x, y-1);
        }
        if(y != n){
            update(q, x, y, x, y+1);
        }
    }
    s[n][n] = 0;
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            ans += (long long)(s[i][j] - a[i][j]);
        }
    }
    printf("%lld", ans);
}