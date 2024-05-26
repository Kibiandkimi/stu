//
// Created by kibi on 2021/9/25.
//
#include <bits/stdc++.h>
using namespace std;
long long n,m=1e9+7,a[100005],f[100005],w[100005];
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    f[0] = 1;
    for(int i = 1; i <= n; i++){
        long long t = sqrt(a[i]), tt = 0;
        for(int j = 1; j <= t; j++){
            if(a[i]%j==0){
                w[++tt]=j;
                if(j*j!=a[i]){
                    w[++tt]=a[i]/j;
                }
            }
        }
        sort(w+1, w+tt+1);
        for(int j = tt; j >= 1; j--){
            f[w[j]] = (f[w[j]]+f[w[j]-1])%m;
        }
    }
    long long s = 0;
    for(int i = 1; i <= n; i++){
        s = (s+f[i])%m;
    }
    cout << s;
}