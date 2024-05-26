//
// Created by kibi on 23-11-13.
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

    int n;
    read({&n});

    int raw[n];
    for(auto &i : raw){
        read({&i});
    }

    if(n & 1){
        printf("YES\n%d\n", n - 1);
        for(int i = 1; i < n; i += 2){
            printf("%d %d %d\n", i, i + 1, i + 2);
        }
        for(int i = 1; i < n; i += 2){
            printf("%d %d %d\n", n, i, i + 1);
        }
    }else{
        int res = 0;
        for(auto &i : raw){
            res ^= i;
        }
        if(res != 0){
            printf("NO\n");
            return 0;
        }
        n--;
        printf("YES\n%d\n", n - 1);
        for(int i = 1; i < n; i += 2){
            printf("%d %d %d\n", i, i + 1, i + 2);
        }
        for(int i = 1; i < n; i += 2){
            printf("%d %d %d\n", n, i, i + 1);
        }
    }
}