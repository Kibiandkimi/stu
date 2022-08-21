//
// Created by kibi on 2022/8/17.
//
//28pts
//#include <bits/stdc++.h>
//using namespace std;
//int n, m, p;
//int v[1005][1005], w[1005];
//int d[1005];
//bool vis[1005];
//
//int main(){
//    scanf("%d %d %d", &n, &m, &p);
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= m; j++){
//            scanf("%d", &v[i][j]);
//        }
//    }
//    for(int j = 1; j <= m; j++){
//        v[0][j] = v[n][j];
//    }
//    for(int i = 1; i <= n; i++){
//        scanf("%d", &w[i]);
//    }
//    memset(d, 0xc0, sizeof d);
//    d[0] = 0;
//    vis[0] = true;
//    for(int i = 1; i <= n; i++){
//        for(int j = 0; j < m; j++){
//            if(vis[j]){
//                int s = 0;
//                int mxk = min(p, m-j);
//                for(int k = 1; k <= mxk; k++){
//                    s += v[(i+k-1)%n][k+j];
//                    d[j+k] = max(d[j+k], d[j]+s-w[i]);
//                    vis[j+k] = true;
//                }
//            }
//        }
//    }
//    printf("%d", d[m]);
//}
#include <bits/stdc++.h>
using namespace std;
int n, m, p;
int f[1005][1005], cost[1005], q[1005][1005], loc[1005][1005], l[1005], r[1005], add[1005], dp[1005];

int get(int i, int j){
    return ((j-i)%n+n)%n;
}

int main(){
    scanf("%d %d %d", &n, &m, &p);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &f[j][i]);
            f[j][i] += f[j-1][i-1];
        }
    }
    for(int i = 0; i < n; i++){
        scanf("%d", &cost[i]);
        q[i][++r[i]] = -cost[i];
        l[i]++;
    }
    memset(dp, 0xc0, sizeof dp);
    dp[0] = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < n; j++){
            int id = get(i, j);
            while(l[id]<=r[id]&&loc[id][l[id]]+p<i){
                l[id]++;
            }
            if(!j){
                add[id] += f[i][n];
            }
            if(l[id]<=r[id]){
                dp[i] = max(dp[i], q[id][l[id]]+add[id]+f[i][j]);
            }
        }
        for(int j = 0; j < n; j++){
            int id = get(i, j);
            int tmp = dp[i]-add[id]-f[i][j]-cost[j];
            while(l[id]<=r[id]&&q[id][r[id]]<=tmp){
                r[id]--;
            }
            loc[id][++r[id]] = i;
            q[id][r[id]] = tmp;
        }
    }
    printf("%d", dp[m]);
}