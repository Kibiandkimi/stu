//
// Created by kibi on 24-7-16.
//
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

    auto read_mp = [](bool &x){
        int c = getchar();
        while(c != '.' && c != 'X'){
            c = getchar();
        }
        x = (bool)(c == '.');
    };

    static int n = 0, m = 0;
    read(n), read(m);

    bool mp[2][n];
    for(auto &i : mp){
        for(auto &j : i){
            read_mp(j);
        }
    }

    int f[2 * n][20];
    f[n - 1][0] = n - 1;
    f[2 * n - 1][0] = 2 * n - 1;
    for(int i = 0; i < n - 1; i++){
        if(mp[0][i]){
            if(mp[0][i + 1]){
                f[i][0] = i + 1;
            }else if(mp[1][i]){
                f[i][0] = i + n;
            }else{
                f[i][0] = i;
            }
        }
        if(mp[1][i]){
            if(mp[1][i + 1]){
                f[i + n][0] = i + n + 1;
            }else if(mp[0][i]){
                f[i + n][0] = i;
            }else{
                f[i + n][0] = i + n;
            }
        }
    }

    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            if(mp[0][j]){
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
            if(mp[1][j]){
                f[j + n][i] = f[f[j + n][i - 1]][i - 1];
            }
        }
    }

    auto cmp = [](int u, int v){
        if(u >= n && v >= n || u < n && v < n){
            return u > v;
        }else if(u >= n){
            return (u - n) > v;
        }else{
            return u > (v - n);
        }
    };

    while(m--){
        int u, v;
        read(u), read(v);
        u--, v--;
        cmp(u, v) ? swap(u, v) : void(0);

        if(cmp(v, f[u][19])){
            printf("-1\n");
            continue;
        }else if (u == v + n || v == u + n)[[unlikely]]{
            printf("1\n");
            continue;
        }else if(u == v)[[unlikely]]{
            printf("0\n");
            continue;
        }

        int ans = 0;

        for(int i = 19; i >= 0; i--){
            if(cmp(v, f[u][i])){
                u = f[u][i];
                ans += (1 << i);
            }
        }

        if(u >= n && v < n || u < n && v >= n){
            ans += 2;
        }else{
            ans += 1;
        }
        printf("%d\n", ans);
    }
}