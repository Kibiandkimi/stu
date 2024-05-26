//
// Created by kibi on 23-11-15.
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

    freopen("t.in", "r", stdin);
    freopen("t.out", "w", stdout);

    int n;
    read({&n});

    if(n == 1){
        printf("0\n0\n");
        return 0;
    }

    bool graph[n][n];
    int ans = n * (n - 1) * (n - 2) * (n - 3) / (4 * 3 * 2 * 1) - n * (n - 3) * (n - 5) * (n - 7) / (2 * 4 * 3 * 2 * 1);
    for(int i = 0; i < n; i++){
        int pre = i + n / 2 + 1;
        graph[i][i] = false;
        for(int j = 1; j < n; j++){
            if(i + j <= pre){
                graph[i][(i + j) % n] = true;
            }else if(i + j > pre){
                graph[i][(i + j) % n] = false;
            }
        }
    }

    printf("%d\n", ans);
    for(auto &i : graph){
        for(auto j : i){
            printf("%d ", (int)j);
        }
        printf("\n");
    }
}