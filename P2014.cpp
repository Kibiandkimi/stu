//
// Created by kibi on 2021/8/10.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,dp[305][305];
// struct node{
//     int v,w;
// };
vector<int> a[305];
int f(int x){
    for(int i = 0; i < a[x].size(); i++){
        int t = a[x][i];
        f(t);
        for(int j = m+1; j >= 1; j--){
            for(int k = 0; k < j; k++){
                dp[x][j] = max(dp[x][j], dp[t][k]+dp[x][j-k]);
            }
        }
    }
    return 0;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(i);
        dp[i][1] = v;
    }
    f(0);
    cout << dp[0][m+1];
    return 0;
}