//
// Created by kibi on 2022/8/17.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int a[105];
int num[305], s[305], f1[305][305], f2[305][305], mn, mx;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n+n; i++){
        a[i+n] = a[i];
        s[i] = s[i-1] + a[i];
    }
    for(int p = 1; p < n; p++){
        for(int i = 1, j = i+p; (j<n+n)&&(i<n+n); i++,j=i+p){
            f2[i][j] = 1e9;
            for(int k = i; k < j; k++){
                f1[i][j] = max(f1[i][j], f1[i][k]+f1[k+1][j]+(s[j]-s[i-1]));
                f2[i][j] = min(f2[i][j], f2[i][k]+f2[k+1][j]+(s[j]-s[i-1]));
            }
        }
    }
    mn = 1e9;
    for(int i = 1; i <= n; i++){
        mx = max(mx, f1[i][i+n-1]);
        mn = min(mn, f2[i][i+n-1]);
    }
    printf("%d\n%d", mn, mx);
}