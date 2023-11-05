//
// Created by kibi on 23-11-4.
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

    auto read_str = [](vector<int> &x){
        static auto judge = [](int c){return 'a' <= c && c <= 'z';};
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        while(judge(c)){
            x.emplace_back(c);
            c = getchar();
        }
        x.shrink_to_fit();
    };

    auto read_c = [](int &x){
        static auto judge = [](int c){return 'a' <= c && c <= 'z';};
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        x = c;
    };

    int n, m;
    read(n), read(m);

    vector<int> str;
    read_str(str);

    int cost[26];
    for(int i = 0; i < n; i++){
        int x, add, del;
        read_c(x), read(add), read(del);
        cost[x - 'a'] = min(add, del);
        // cost[0][c - 'a'] = add;
        // cost[1][c - 'a'] = del;
    }

    int f[m][m];
    for(int i = 0; i < m; i++){
        f[i][i] = 0;
    }
    for(int len = 2; len <= m; len++){
        for(int i = 0; i <= m - len; i++){
            int j = i + len - 1;
            f[i][j] = min(f[i][j - 1] + cost[str[j] - 'a'], f[i + 1][j] + cost[str[i] - 'a']);
            if(str[i] == str[j] && len > 2){
                f[i][j] = min(f[i][j], f[i + 1][j - 1]);
            }else if(str[i] == str[j]){
                f[i][j] = 0;
            }
        }
    }

    printf("%d\n", f[0][m - 1]);
}