//
// Created by kibi on 2022/4/4.
//
#include <bits/stdc++.h>
using namespace std;
string txt, pat;
int dp[1000005][256];
int x;
int l1, l2;
int ans = -1;
int X[1000005];
int main(){
    cin >> txt >> pat;
    l1 = pat.length();
    l2 = txt.length();
    dp[0][pat[0]] = 1;
    for(int i = 1; i <= l1; i++){
        for(int j = 0; j < 256; j++){
            dp[i][j] = dp[x][j];
        }
        dp[i][pat[i]] = i+1;
        x = dp[x][pat[i]];
        X[i] = x;
        //        mxx = max(mxx,x);
    }
    int j = 0;
    for(int i = 0; i < l2; i++){
        j = dp[j][txt[i]];
        if(j == l1){
            ans = i - l1 + 2;
            printf("%d\n", ans);
        }
    }
    //    if(ans == -1){
    //        printf("-1\n");
    //    }
    //    printf("%d", mxx);
    for(int i = 0; i < l1; i++){
        printf("%d ", X[i]);
    }
}