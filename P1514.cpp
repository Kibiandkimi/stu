//
// Created by Lenovo on 24-5-16.
//
// TODO 24-5-16
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            if(c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    };

    int n, m;
    read(n), read(m);

    int altitude[n][m];

    for (auto &i : altitude){
        for (auto &j : i){
            read(j);
        }
    }

    // bfs
    int res[m][2];
    int vis[n][m];
    memset(vis, 0x3f, sizeof vis);
    bool ava[m];
    memset(ava, 0, sizeof ava);
    for (int i = 0; i < m; i++){
        static const int dir[4][2] = {
                {0, 1},
                {1, 0},
                {0, -1},
                {-1, 0}
        };
        stack<tuple<int, int> > stk;
        stk.emplace(0, i);
        while(!stk.empty()){
            auto [x, y] = stk.top();
            stk.pop();
            for (auto &j : dir){
                int p = x + j[0], q = y + j[1];
                if(p >= 0 && p < n && q >= 0 && q < m && vis[p][q] != i && altitude[p][q] < altitude[x][y]){
                    stk.emplace(p, q);
                    vis[p][q] = i;
                }
            }
            for (int j = 0; j < m; j++){
                if(vis[n - 1][j] == i){
                    res[i][0] = j;
                    break;
                }
            }
            for (int j = m - 1; j >= 0; j--){
                if(vis[n - 1][j] == i){
                    res[i][1] = j;
                    break;
                }
            }
            for(int j = 0; j < m; j++){
                ava[j] |= (vis[n - 1][j] == i);
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < m; i++){
        ans += !ava[i];
    }
    if(ans){
        printf("0\n%d", ans);
        return 0;
    }

    int f[m];
    memset(f, 0x3f, sizeof f);
    int temp = 0;
    for(int i = 0; i < m; i++){
        if(res[i][0] == 0){
            temp = max(temp, res[i][1]);
        }
    }
    f[temp] = 1;
    for(int i = temp + 1; i < m; i++){
        for(int j = temp + 1; j <= i; j++){
            for(int k = 0; k < m; k++){
                if(res[k][0] <= j && res[k][1] >= i){
                    f[i] = min(f[i], f[j - 1] + 1);
                    break;
                }
            }
        }
    }

    printf("1\n%d", f[m - 1]);
}