//
// Created by kibi on 2021/8/12.
//
#include <bits/stdc++.h>
using namespace std;
int n,a[200005],f[200005],mx=-1e9;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    f[1] = a[1];
    for(int i = 2; i <= n; i++){
        f[i] = max(f[i-1]+a[i], a[i]);
        mx = max(mx, f[i]);
    }
    cout << mx;
}