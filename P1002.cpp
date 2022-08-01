//
// Created by kibi on 2021/8/31.
//
#include <bits/stdc++.h>
using namespace std;
long long n,m,x,y;
long long a[50][50],d[50][50];
int main(){
    cin >> n >> m >> x >> y;
    //a[(x - 1)>=0?(x - 1):30][(y - 2)>=0?(y - 2):30] = a[(x - 2)>=0?(x - 2):30][(y - 1)>=0?(y - 1):30] = a[x + 1][(y - 2)>=0?(y - 2):30] = a[x + 2][(y - 1)>=0?(y - 1):30] = a[(x - 1)>=0?(x - 1):30][y + 2] = a[(x - 2)>=0?(x - 2):30][y + 1] = a[x + 1][y + 2] = a[x + 2][y + 1] = a[x][y] = 1;
    a[x][y] = 1;
    a[x+1][y+2] = 1;
    a[x+2][y+1] = 1;
    if(x-1>=0){
        a[x-1][y+2] = 1;
    }
    if(x-2>=0){
        a[x-2][y+1] = 1;
    }
    if(y-1>=0){
        a[x+2][y-1] = 1;
    }
    if(y-2>=0){
        a[x+1][y-2] = 1;
    }
    if(y-2>=0&&x-2>=0){
        a[x-1][y-2] = 1;
        a[x-2][y-1] = 1;
    }
    d[0][0] = 1;
    for(long long i = 0; i <= n; i++){
        if(a[i][0]){
            break;
        }
        d[i][0] = 1;
    }
    for(long long j = 0; j <= m; j++){
        if(a[0][j]){
            break;
        }
        d[0][j] = 1;
    }
    for(long long i = 1; i <= n; i++){
        for(long long j = 1; j <= m; j++){
            if(a[i][j])continue;
            d[i][j] = d[i-1][j]+d[i][j-1];
        }
    }
    printf("%lld", d[n][m]);
}