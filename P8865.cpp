//
// Created by kibi on 23-11-1.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void read(int &x){
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
        }
    };

    auto read = Tools::read;

    int T, id;
    read(T), read(id);

    while(T--){
        int n, m, s1, s2;
        read(n), read(m), read(s1), read(s2);

        vector<vector<bool>> mp(n, vector<bool>(m, false));
        for(auto &i : mp){
            for(auto &j : i){
                int t;
                read(t);
                j = t;
            }
        }

        int f[n][m];
        for(int i = 0; i < n; i++){
            f[i][m - 1] = 0;
            for(int j = m - 2; j >= 0; j++){
                if(mp[i][j]){
                    f[i][j] = -1;
                }else{
                    f[i][j] = f[i][j + 1] + 1;
                }
            }
        }

        for(int j = 1; j < m; j++){

        }
    }
}