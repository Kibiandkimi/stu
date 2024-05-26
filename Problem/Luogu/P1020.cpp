//
// Created by kibi on 2021/10/16.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005];
int dp[100005], dp2[100005],len = 1;
bool cmp(int a, int b){
    return a>b;
}
int main(){
    while(scanf("%d", &a[n+1])!=-1){
        n++;
    }
    //    int mx = 1;
    dp[1] = a[1];
    len = 1;
    for(int i = 2; i <= n; i++){
        //        dp[i] = 1;
        //        for(int j = 1; j <= i-1; j++){
        //            dp[i] = max(dp[i], a[i]<=a[j]?dp[j]+1:0);
        //        }
        //        mx = max(mx, dp[i]);
        if(a[i]<=dp[len]){
            dp[++len] = a[i];
        }else{
            int p = upper_bound(dp + 1, dp + 1 + len, a[i], cmp) - dp;
            dp[p] = a[i];
        }
    }
    cout << len;
    len = 1;
    dp2[1] = a[1];
    for(int i = 1; i <= n; i++){
        //        dp2[i] = 1;
        //        for(int j = 1; j <= i-1; j++){
        //            dp2[i] = max(dp2[i], a[i]>a[j]?dp2[j]+1:0);
        //        }
        //        mx = max(mx, dp2[i]);
        if(a[i] > dp2[len]){
            dp2[++len] = a[i];
        }else{
            int p = lower_bound(dp2 + 1, dp2 + 1 + len, a[i]) - dp2;
            dp2[p] = a[i];
        }
    }

    cout << endl << len;
}