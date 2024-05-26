//
// Created by kibi on 2022/8/27.
//
//T1
#include <bits/stdc++.h>
using namespace std;
static const int mod = 998244353;
int n, q, a[505][2];
int d[505][505][105];
bool vis[505];

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

int main(){
    read(n);
    read(q);
    for(int i = 1; i <= n; i++){
        read(a[i][0]);
        read(a[i][1]);
        for(int j = a[i][0]; j <= a[i][1]; j++){
            //            d[i][j][1]++;
            //            d[i][j+1][1]--;
            d[i][j][1] = 1;
        }
        d[i][i][0] = 1;
        //        d[i][i][0]++;
        //        d[i][i+1][0]--;
    }
    for(int t = 1; t <= 100; t++){
        for(int i = 1; i <= n; i++){
            int u = a[i][0], v = a[i][1];
            int tt[505], cnt = 0;
            for(int j = 1; j <= n; j++){
                if(d[j][i][t]){
                    tt[++cnt] = j;
                }
            }
            for(int k = 1; k <= cnt; k++){
                //                for(int j = u; j <= v; j++){
                ////                d[i][u][t+1] = d[i][i][t]+1;
                //                    d[tt[k]][j][t+1] = (d[tt[k]][j][t+1]+d[tt[k]][i][t])%mod;
                //                }
                d[tt[k]][u][t+1] = (d[tt[k]][u][t+1]+d[tt[k]][i][t])%mod;
                d[tt[k]][v+1][t+1] = (d[tt[k]][v+1][t+1]-d[tt[k]][i][t]);
                if(d[tt[k]][v+1][t+1]<0){
                    d[tt[k]][v+1][t+1] += mod;
                }
                d[tt[k]][v+1][t+1] %= mod;
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                d[i][j][t] = d[i][j][t]+d[i][j-1][t];
                if(d[i][j][t]<0){
                    d[i][j][t] += mod;
                }
                d[i][j][t] %= mod;
            }
        }
    }
    while(q--){
        int ta, tb, tc, tm;
        read(ta), read(tb), read(tc), read(tm);
        int js = 0;
        if(ta == tc || tb == tc){
            printf("0\n");
            continue;
        }
        //        TODO 计算从ta经过tc到达tb的总数js
        int jj = 0, oo = 0;
        for(int t = 1; t < tm; t++){

        }
        for(int t = 1; t < tm; t++){
            js = (js+((long long)d[ta][tc][t]*d[tc][tb][tm-t]%mod))%mod;
        }
        //        end
        int s = d[ta][tb][tm];
        if(s < js){
            s = (s+mod-js)%mod;
        }else{
            s = s-js;
        }
        printf("%d\n", s);
    }
}