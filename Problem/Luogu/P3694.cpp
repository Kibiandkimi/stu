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

    int n, m;
    read({&n, &m});

    int num[m], data[n], sum[m][n];
    memset(num, 0, sizeof num);
    memset(sum, 0, sizeof sum);
    read({&data[0]});
    data[0]--;
    sum[data[0]][0] = 1, num[data[0]]++;
    for(int i = 1; i < n; i++){
        read({&data[i]});
        data[i]--;
        for (int j = 0; j < m; ++j){
            sum[j][i] = sum[j][i - 1];
        }
        sum[data[i]][i]++;
        num[data[i]]++;
    }

    int f[1 << m];
    memset(f, -1, sizeof f);
    f[0] = 0;
    for(int i = 1; i < (1 << m); i++){
        int len = 0;
        for(int j = 0; j < m; j++){
            if(i & (1 << j)){
                len += num[j];
            }
        }
        for(int j = 0; j < m; j++){
            if(i & (1 << j)){
                int l = len - num[j] - 1, r = len - 1;
                int val = f[i ^ (1 << j)] + num[j] - (sum[j][r] - (l == -1 ? 0 : sum[j][l]));
                f[i] = f[i] == -1 ? val : min(f[i], val);
            }
        }
    }
    printf("%d\n", f[(1 << m) - 1]);
}