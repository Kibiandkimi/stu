//
// Created by kibi on 2021/8/31.
//
#include <bits/stdc++.h>
using namespace std;
int n,a[15][15],d[15][15][30],step;
bool add(){
    int x,y,s;
    scanf("%d %d %d", &x, &y, &s);
    if((!x)&&(!y)&&(!s)){
        return false;
    }
    a[x][y] = s;
    return true;
}
int main(){
    cin >> n;
    step = n*2-1;
    while(add()){}
    for(int i = 1; i <= step; i++){
        int mx = min(n,i);
        for(int j = 1; j <= mx; j++){
            for(int k = 1; k <= mx; k++){
                d[j][k][i] = max(d[j-1][k-1][i-1], max(d[j-1][k][i-1], max(d[j][k-1][i-1], d[j][k][i-1])))+a[j][i-j+1]+a[k][i-k+1];
                if(j==k){
                    d[j][k][i]-=a[j][i-j+1];
                }
            }
        }
    }
    cout << d[n][n][step];
    return 0;
}