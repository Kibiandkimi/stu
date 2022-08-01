//
// Created by kibi on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
int k,n;
int p[20], sta[17];
// vector<int> s[20];
double dp[105][1<<16];
int main(){
    scanf("%d %d", &k, &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &p[i]);
        int t;
        scanf("%d", &t);
        while(t){
            // s[i].push_back(t);
            sta[i] |= (1<<(t-1));
            scanf("%d", &t);
        }
    }
    for(int i = k; i >= 1; i--){
        for(int j = 0; j < (1<<n); j++){
            for(int k = 1; k <= n; k++){
                if((j&sta[k])==sta[k]){
                    dp[i][j] += max(dp[i+1][j], dp[i+1][j|(1<<(k-1))]+p[k]);
                }else{
                    dp[i][j] += dp[i+1][j];
                }
            }
            dp[i][j] /= n;
        }
    }
    printf("%.6lf", dp[1][0]);
}