//
// Created by kibi on 23-11-7.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](initializer_list<int*> x){
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

        for(auto &i : x){
            read(*i);
        }
    };

    auto read_ = [](int &x){
        auto judge = [](int c){return c == 'R' || c == 'G' || c == 'B' || c == 'Y';};
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        x = c;
    };

    static int n, m, q;
    read({&n, &m, &q});

    int mx_len = min(n / 2, m / 2);

    vector<int> raw_mp[n];
    for(auto &i : raw_mp){
        i = vector<int>(m);
        for(auto &j : i){
            read_(j);
        }
    }

    static auto mp = raw_mp;

    // 2 4 8 16 32 64 128 256
    bool num[mx_len][n][m];
    memset(num, 0, sizeof num);

    auto check = [](int x, int y){
        static int len;
        auto check = [](int x, int y, int col){
            for(int i = x; i < x + len; i++){
                if(mp[i][y] != col){
                    return false;
                }
            }
            for(int j = y; j < y + len; j++){
                if(mp[x][j] != col){
                    return false;
                }
            }
            return true;
        };
        len = 1;
        while(check(x, y, 'R') &&
               check(x, y + len, 'G') &&
               check(x + len, y, 'Y') &&
               check(x + len, y + len, 'B')){
            x--, y--;
            if(x < 0 || y < 0){
                return len;
            }
            len++;
            if(x + len + len > n || y + len + len > m){
                return len - 1;
            }
        }
        return len - 1;
    };

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(raw_mp[i][j] == 'R'){
                int res = check(i, j);
                for(int len = 1; len <= res; len++){
                    int l = len - 1;
                    num[l][i - l][j - l] = true;
                }
            }
        }
    }

    static auto sum = new vector<vector<vector<int>>>(mx_len, vector<vector<int>>(n, vector<int>(m)));
    for (int i = 0; i < mx_len; i++) {
        for (int j = 0; j < n; j++) {
            (*sum)[i][j][0] = num[i][j][0];
            for (int k = 1; k < m; k++) {
                (*sum)[i][j][k] = (*sum)[i][j][k - 1] + num[i][j][k];
            }
        }
        for (int k = 0; k < m; k++) {
            for (int j = 1; j < n; j++) {
                (*sum)[i][j][k] = (*sum)[i][j][k] + (*sum)[i][j - 1][k];
            }
        }
    }

    while(q--){
        static int r1, c1, r2, c2;
        read({&r1, &c1, &r2, &c2});
        r1--, c1--, r2--, c2--;

        int l = 0, r = mx_len - 1, res = -1;

        auto judge = [](int len){
            len++;
            int pre_x = r2 - len * 2 + 1, pre_y = c2 - len * 2 + 1;
            if(pre_x >= r1 && pre_y >= c1){
                int res = (*sum)[len - 1][pre_x][pre_y] -
                          (c1 > 0 ? (*sum)[len - 1][pre_x][c1 - 1] : 0) -
                          (r1 > 0 ? (*sum)[len - 1][r1 - 1][pre_y] : 0) +
                          (c1 > 0 && r1 > 0 ? (*sum)[len - 1][r1 - 1][c1 - 1] : 0);
                if(res){
                    return true;
                }
            }
            return false;
        };

        while(l <= r){
            int mid = (l + r) >> 1;
            if(judge(mid)){
                res = mid;
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }

        if(res == -1){
            printf("0\n");
        }else{
            printf("%d\n", (res + 1) * (res + 1) * 4);
        }
    }

}