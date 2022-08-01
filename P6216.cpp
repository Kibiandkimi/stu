//
// Created by kibi on 2022/7/9.
//
#include <bits/stdc++.h>
using namespace std;
int dp[3000005][30];
char s1[3000005], s2[3000005];
int a[3000005];
int d[3000005];
long long as[3000005], ais[3000005];
int n, m, X;
int main(){
    scanf("%d %d", &n, &m);
    scanf("%s %s", s1+1, s2+1);
    //KMP
    X = 0;
    //    dp[1][s2[1]-'a'] = 1;
    dp[0][s2[1]-'a'] = 1;
    for(int j = 1; j <= m+1; j++){
        for(int c = 0; c <= 'z'-'a'; c++){
            if(s2[j+1]-'a' == c){
                dp[j][c] = j+1;
            }else{
                dp[j][c] = dp[X][c];
            }
        }
        X = dp[X][s2[j+1]-'a'];
    }
    int j = 0;
    for(int i = 1; i <= n; i++){
        j = dp[j][s1[i]-'a'];
        if(j == m){
            a[i-m+1] = 1;
        }
    }

    //Manacher
    int l = 0, r = -1;
    d[1] = 1;
    for(int i = 2; i <= n; i++){
        if(i > r){
            int j;
            for(j = 0; s1[i-j]==s1[i+j]&&s1[i+j]!=0&&(i-j>=1&&i+j<=n); j++){}
            j--;
            l = i-j;
            r = i+j;
            d[i] = j+1;
        }else{
            int j = min(r-i+1, d[l+r-i]);
            for(; s1[i-j]==s1[i+j]&&s1[i+j]!=0&&(i-j>=1&&i+j<=n); j++){}
            d[i] += j--;
            l = i-j;
            r = i+j;
        }
    }

    //前缀和
    for(int i = 1; i <= n; i++){
        as[i] = as[i-1] + a[i];
        ais[i] = ais[i-1] + a[i]*i;
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        int l = i-d[i]+1, r = i+d[i]-m;
        if(l>r)continue;
        int mid = (l+r)/2;
        ans += (ais[mid] - ais[l-1]) - (as[mid] - as[l-1]) * (l-1);
        if(mid!=r){
            ans += (as[r] - as[mid]) * (r+1) - (ais[r]-ais[mid]);
        }
    }

    printf("%lld", ans%4294967296);
}