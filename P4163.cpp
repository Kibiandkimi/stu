//
// Created by kibi on 2021/10/2.
//
// ^

#include <bits/stdc++.h>
using namespace std;
int t,a[15],d,len,cnt;
char c[15];
bool b[15];
int dp[1<<11][1005] = {0};
int main(){
    scanf("%d", &t);
    while(t--){
        memset(dp, 0, sizeof(dp));
        scanf("%s%d",c+1,&d);
        len = strlen(c+1);
        cnt = 0;
        for(int i = 1; i <= len; i++){
            a[i] = c[i]-'0';
        }
        dp[0][0] = 1;
        int tt = (1 << len)-1;
        for(int S = 0; S < tt; S++){
            //            bool b[15] = {0};
            memset(b, 0 , sizeof(b));
            for(int j = 1; j <= len; j++){
                if(!(S&(1<<(j-1))) && !b[a[j]]){
                    b[a[j]] = 1;
                    for(int k = 0; k < d; k++){
                        dp[S|(1<<(j-1))][(k*10+a[j])%d] += dp[S][k];
                    }
                }
            }
        }
        printf("%d\n", dp[(1<<len)-1][0]);
    }
}