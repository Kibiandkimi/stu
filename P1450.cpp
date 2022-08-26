//
// Created by kibi on 22-8-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, c[5], a[5];
long long d[100005];

int main(){
    scanf("%d %d %d %d %d", &c[1], &c[2], &c[3], &c[4], &n);
    d[0] = 1;
    for(int i = 1; i <= 4; i++){
        for(int j = c[i]; j <= 100001; j++){
            d[j] += d[j-c[i]];
        }
    }
    while(n--){
        int sum;
        long long res = 0;
        for(int i = 1; i <= 4; i++){
            scanf("%d", &a[i]);
        }
        scanf("%d", &sum);
        for(int i = 0; i <= 15; i++){
            long long t = sum;
            int cnt = 0;
            for(int j = 1; j <= 4; j++){
                if((i>>(j-1))&1){
                    t -= c[j]*(a[j]+1);
                    cnt ^= 1;
                }
            }
            if(t < 0){
                continue;
            }
            if(!cnt){
                res += d[t];
            }else{
                res -= d[t];
            }
        }
        printf("%lld\n", res);
    }
}