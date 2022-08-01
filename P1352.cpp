//
// Created by kibi on 2021/8/6.
//
#include <bits/stdc++.h>
using namespace std;
int n,r[6005],dp[6005][2],a[6005];
vector<int> b[6005];
int f(int x){
    if(!b[x].size()){
        dp[x][0] = 0;
        dp[x][1] = r[x];
        return max(0,dp[x][1]);
    }
    dp[x][1] = r[x];
    for(int i = 0; i < b[x].size(); i++){
        dp[x][0] += f(b[x][i]);
        dp[x][1] += dp[b[x][i]][0];
    }
    return max(dp[x][0],dp[x][1]);
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> r[i];
    }
    for(int i = 1; i < n; i++){
        int l,t;
        cin >> l >> t;
        a[l] = t;
        b[t].push_back(l);
    }
    int root = -1;
    for(int i = 1; i <= n; i++){
        if(!a[i]){
            root = i;
            break;
        }
    }
    cout << f(root);

}