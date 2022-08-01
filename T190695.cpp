//
// Created by kibi on 2021/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[205][205],vis[205][205],ss;
int pd(){
    int s = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            s+=vis[i][j];
        }
    }
    return s;
}
int f(int i, int j){
    if(a[i][j]||vis[i][j]){
        ss = max(ss,pd());
        return 0;
    }
    vis[i][j] = 1;
    for(int ii = 1; ii <= n; ii++){
        for(int jj = 1; jj <= m; jj++){
            f(ii,jj);
        }
    }
    vis[i][j] = 0;
    return 0;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int t;
            cin >> t;
            a[i][j] = t == '.' ? 0 : t == '*' ? 1 : 2;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            f(i,j);
        }
    }
    cout << ss;
}