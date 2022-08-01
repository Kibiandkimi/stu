//
// Created by kibi on 2021/10/16.
//
#include <bits/stdc++.h>
using namespace std;
struct node{
    long long p, t;
};
long long n,k,num = 1;
node a[10005];
long long d[10005];
long long s[10005];
bool cmp(node a, node b){
    return a.p > b.p;
}
int main(){
    scanf("%lld %lld", &n, &k);
    for(int i = 1; i <= k; i++){
        scanf("%lld %lld", &a[i].p, &a[i].t);
        s[a[i].p]++;
    }
    sort(a + 1, a + 1 + k, cmp);
    for(int i = n; i >= 1; i--){
        if(s[i]==0){
            d[i] = d[i+1]+1;
        }else{
            for(int j = 1; j <= k; j++){
                if(a[j].p==i){
                    d[i] = max(d[i+a[j].t], d[i]);
                    // num++;
                }
            }
        }
    }
    printf("%lld", d[1]);
}