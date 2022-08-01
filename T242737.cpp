//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int n;
bool a[1005][25];
int f[300005][2];
int main(){
    scanf("%d", &T);
    while(T--){
        memset(a, 0, sizeof a);
        memset(f, 0, sizeof f);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            int k;
            scanf("%d", &k);
            for(int j = 1; j <= k; j++){
                int t;
                scanf("%d", &t);
                a[i][(int)log(t)] = true;
                //                s[(int)log(t)]++;
            }
        }
        int mx = 20;
        for(int j = 0; j <= 20; j++){
            if(a[1][j]){
                f[j][1] = 1;
            }
        }
        for(int i = 2; i <= n; i++){
            bool flag = i%2;
            for(int j = 0; j <= 20; j++){
                for(int k = 0; k <= mx; k++){
                    if(f[k][!flag] == i-1 && a[i][j]){
                        f[k+j][flag] = i;
                    }
                }
            }
            mx += 20;
        }
        int ans = 0;
        bool flag = n%2;
        for(int i = 0; i <= mx; i++){
            if(f[i][flag] == n){
                ans++;
            }
        }
        printf("%d\n", ans);
    }

}