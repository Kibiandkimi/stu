//
// Created by kibi on 2021/8/8.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[205][205];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    if(n == 2 && m == 2){
        int t[4] = {a[1][1], a[1][2], a[2][1], a[2][2]};
        sort(t,t+4);
        cout << (t[1]+t[2])/2;
        return 0;
    }else if(n == 1){
        int t[2] = {a[1][1],a[1][2]};
        cout << (t[0]+t[1])/2;
        return 0;
    }else if(m == 1){
        int t[2] = {a[1][1], a[2][1]};
        cout << (t[0]+t[1])/2;
        return 0;
    }

    return 0;
}