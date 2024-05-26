//
// Created by kibi on 2021/8/16.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,w[105][105];
// vector<int> a[105];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = i+1; j <= n; j++){
            w[i][j] = w[j][i] = 1e9;
        }
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        w[u][v] = 1;
        w[v][u] = 2;
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(w[i][k]==w[k][j]&&w[i][k]!=1e9){
                    w[i][j] = w[i][k];
                    w[j][i] = w[i][j]==1?2:1;
                }
            }
        }
    }
    int s = 0;
    for(int i = 1; i <= n; i++){
        bool flag = true;
        for(int j = 1; j <= n; j++){
            if(w[i][j] == 1e9){
                flag = false;
                j = n+1;
            }
        }
        s+=flag;
    }
    cout << s;
}
