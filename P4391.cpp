//
// Created by kibi on 2022/4/4.
//
//89pt
#include <bits/stdc++.h>
using namespace std;
int n;
int x;
int mxx;
string s1;
int dp[1000005][26];
int l;
int main(){
    scanf("%d", &n);
    cin >> s1;
    l = s1.length();
    dp[0][s1[0]-'a'] = 1;
    for(int i = 1; i < l; i++){
        for(int j = 0; j < 26; j++){
            dp[i][j] = dp[x][j];
        }
        dp[i][s1[i]-'a'] = i + 1;
        x = dp[x][s1[i]-'a'];
        mxx = max(mxx, x);
    }
    cout << n - mxx;
}