//
// Created by kibi on 2022/4/4.
//
//89pt(100pts在下面)
//#include <bits/stdc++.h>
//using namespace std;
//int n;
//int x;
//int mxx;
//string s1;
//int dp[1000005][26];
//int l;
//int main(){
//    scanf("%d", &n);
//    cin >> s1;
//    l = s1.length();
//    dp[0][s1[0]-'a'] = 1;
//    for(int i = 1; i < l; i++){
//        for(int j = 0; j < 26; j++){
//            dp[i][j] = dp[x][j];
//        }
//        dp[i][s1[i]-'a'] = i + 1;
//        x = dp[x][s1[i]-'a'];
//        mxx = max(mxx, x);
//    }
//    cout << n - mxx;
//}

#include <bits/stdc++.h>
using namespace std;
int n;
char c[1000005];
int dp[1000005][26];
int ans;

int main(){
    scanf("%d", &n);
    scanf("%s", c+1);
    dp[1][c[1]-'a'] = 2;
    for(int i = 2, j = 1; i <= n; i++){
        for(int k = 0; k < 26; k++){
            dp[i][k] = dp[j][k];
        }
        dp[i][c[i]-'a'] = i+1;
        j = dp[j][c[i]-'a'];
        j?:j=1;
        //        printf("%d ", j);
        ans = max(ans, i - j);
    }
    //    printf("\n");
    //    int mxx = 0;
    //    for(int i = 0; i < 26; i++){
    //        mxx = max(mxx, dp[n][i]);
    //    }
    //    for(int i = 1; i <= n; i++){
    //        printf("%d: ", i);
    //        for(int j = 0; j < 3; j++){
    //            printf("%d ", dp[i][j]);
    //        }
    //        printf("\n");
    //    }
    //    printf("\n");
    printf("%d", ans+1);
}