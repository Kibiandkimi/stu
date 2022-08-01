//
// Created by kibi on 2021/8/31.
//
#include <bits/stdc++.h>
using namespace std;
int n,W,head,tail,ans,dp[40005],q1[40005],q2[40005];
int main(){
    scanf("%d %d", &n, &W);
    for(int i = 1; i <= n; i++){
        int v,w,c;
        scanf("%d %d %d", &v, &w, &c);
        if(!w){
            ans += v*c;
        }
        c = min(c,W/w);
        for(int d = 0; d < w; d++){
            head = tail = 0;
            int k = (W-d)/w;
            for(int j = 0; j <= k; j++){
                while(head<tail&&dp[d+j*w]-j*v>=q2[tail-1]){
                    tail--;
                }
                q1[tail] = j;
                q2[tail++] = dp[d+j*w]-j*v;
                while(head < tail&&q1[head] < j-c){
                    head++;
                }
                dp[d+j*w] = max(q2[head]+j*v, dp[d+j*w]);
            }
        }
    }
    cout << ans+dp[W];
    return 0;
}