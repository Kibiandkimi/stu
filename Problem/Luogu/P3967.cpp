//
// Created by kibi on 2022/7/14.
//
#include <bits/stdc++.h>
using namespace std;
int n, w[85][85], lx[85], ly[85], slack[85], link[85], pre[85];
bool vis[85];

struct node{
    int l, r;
}r[85];

void bfs(int u){
    int x, y = 0, yy = 0, delta;
    memset(pre, 0, sizeof pre);
    link[y] = u;
    memset(slack, 0x3f, sizeof slack);

    while(true){
        x = link[y];
        delta = 0x3f3f3f3f;
        vis[y] = true;

        for(int i = 1; i <= n; i++) {
            if (vis[i]) {
                continue;
            }
            if (slack[i] > lx[x] + ly[i] - w[x][i]){
                slack[i] = lx[x] + ly[i] - w[x][i];
                pre[i] = y;
            }
            if(slack[i] < delta){
                delta = slack[i];
                yy = i;
            }
        }

        for(int i = 0; i <= n; i++){
            if(vis[i]){
                lx[link[i]] -= delta;
                ly[i] += delta;
            }else{
                slack[i] -= delta;
            }
        }

        y = yy;

        if(link[y] == -1){
            break;
        }
    }

    while(y){
        link[y] = link[pre[y]];
        y = pre[y];
    }

}

int KM(){
    memset(link, -1, sizeof link);

    for(int i = 1; i <= n; i++){
        memset(vis, 0, sizeof vis);
        bfs(i);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += w[link[i]][i];
    }
    return ans;
}

bool cmp(node a, node b){
    return a.l < b.l;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &w[i][j]);
        }
    }

    int ans = KM();
    printf("%d\n", ans);

    for(int i = 1; i <= n; i++){
        r[i].l = link[i];
        r[i].r = i;
    }
    sort(r+1, r+n+1, cmp);

    for(int i = 1; i <= n; i++){
        int t = w[r[i].l][r[i].r];
        w[r[i].l][r[i].r] = -0x3f3f3f3f;
        if(KM() != ans){
            printf("%d %d\n", r[i].l, r[i].r);
        }
        w[r[i].l][r[i].r] = t;
    }

    return 0;
}