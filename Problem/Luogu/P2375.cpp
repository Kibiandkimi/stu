//
// Created by kibi on 2022/4/4.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int l;
int dp[1000005][26];
int ans;
int x;
int num[1000005];
int X[1000005];
string s;
int mod = 1e9+7;
int main(){
    scanf("%d", &T);
    while(T--){
        ans = 1;
        num[1] = 1;
        cin >> s;
        l = s.length();
        dp[0][s[0]-'a'] = 1;
        x = 0;
        for(int i = 1; i < l; i++){
            for(int j = 0; j < 26; j++){
                dp[i][j] = dp[x][j];
            }
            dp[i][s[i]-'a'] = i + 1;
            x = dp[x][s[i]-'a'];
            X[i] = x;
            num[i+1] = num[x]+1;
        }
        x = 0;
        for(int i = 1; i < l; i++){
            //            for(int j = 0; j < 26; j++){
            //                dp[i][j] = dp[x][j];
            //            }
            //            dp[i][s[i]-'a'] = i + 1;
            x = dp[x][s[i]-'a'];
            while((x*2)>(i+1)){
                x = X[x-1];
            }
            ans = (ans*(long long)(num[x]+1))%mod;
        }
        printf("%lld\n", ans);
    }
}