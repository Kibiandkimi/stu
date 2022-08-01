//
// Created by kibi on 2021/9/8.
//
#include <bits/stdc++.h>
using namespace std;
int p,q,d[1005][1005],a[1005];
int main(){
    cin >> p >> q;
    for(int i = 1; i <= q; i++){
        cin >> a[i];
        d[i][i] = p-1;
    }
    a[q+1] = p+1;a[0] = 0;
    sort(a+1, a+1+q);
    for(int l = 1; l <= q; l++){
        for(int i = 1; i+l-1 <= q; i++){
            int j = i+l-1;
            d[i][j] = 1e9;
            for(int k = i; k <= j; k++){
                d[i][j] = min(d[i][j], d[i][k-1]+d[k+1][j]+a[j+1]-a[i-1]-2);
            }
        }
    }
    printf("%d", d[1][q]);
    return 0;
}