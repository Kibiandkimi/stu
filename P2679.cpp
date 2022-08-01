//
// Created by kibi on 2021/10/1.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
long long d[1010][1010],sum[1010][1010],mod = 1e9+7;
char a[1010],b[1010];
int main(){
    cin >> n >> m >> k;
    cin >> a >> b;
    d[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= 1; j--){
            for(int kk = k; kk >= 1; kk--){
                sum[j][kk] = a[i-1]==b[j-1]?(sum[j-1][kk]+d[j-1][kk-1]):0;
                d[j][kk] = (d[j][kk]+sum[j][kk])%mod;
            }
        }

    }
    cout << d[m][k];
}