#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[1005][1005];
int s[1005][1005];
int main(){
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        int x,y;
        scanf("%d %d", &x, &y);
        a[x][y]++;
    }
    for(int i = 1; i <= 1000; i++){
        for(int j = 1; j <= 1000; j++){
            s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
        }
    }
    for(int i = 1; i<=q; i++){
        int xl,yl,xr,yr;
        scanf("%d %d %d %d", &xl, &yl, &xr, &yr);
        xl--;
        yl--;
        int ss = s[xr][yr]-s[xl][yr]-s[xr][yl]+s[xl][yl];
        printf("%d\n",ss);
    }
}