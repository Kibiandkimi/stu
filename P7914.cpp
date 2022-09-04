//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int n, k;
long long dp[505][505][6];
char s[505];

void read(int &x);

int main(){
    read(n), read(k);
    scanf("%s", s+1);
    for(int i = 1; i <= n; i++){
        dp[i][i-1][0] = 1;
    }
    for(int len = 1; len <= n; len++){
        for(int l = 1; l <= n-len+1; l++){
            int r = l+len-1;
            if(len <= k){
                dp[l][r][0] = dp[l][r-1][0]&&(s[r]=='*'||s[r]=='?');
            }
            if(len >= 2){
                if((s[l]=='('||s[l]=='?')&&(s[r]==')'||s[r]=='?')){
                    dp[l][r][1] = (dp[l+1][r-1][0]+dp[l+1][r-1][2]+dp[l+1][r-1][3]+dp[l+1][r-1][4])%mod;
                }
                for(int i = l; i <= r-1; i++){
                    dp[l][r][2] = (dp[l][r][2]+dp[l][i][3]*dp[i+1][r][0])%mod;
                    dp[l][r][3] = (dp[l][r][3]+(dp[l][i][2]+dp[l][i][3])*dp[i+1][r][1])%mod;
                    dp[l][r][4] = (dp[l][r][4]+(dp[l][i][4]+dp[l][i][5])*dp[i+1][r][1])%mod;
                    dp[l][r][5] = (dp[l][r][5]+dp[l][i][4]*dp[i+1][r][0])%mod;
                }
            }
            dp[l][r][5] = (dp[l][r][5]+dp[l][r][0])%mod;
            dp[l][r][3] = (dp[l][r][3]+dp[l][r][1])%mod;
        }
    }
    printf("%lld\n", dp[1][n][3]);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}