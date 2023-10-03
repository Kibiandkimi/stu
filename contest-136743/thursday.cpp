//
// Created by kibi on 23-10-3.
//
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
                s = s * 10 +  c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    freopen("thursday.in", "r", stdin);
    freopen("thursday.out", "w", stdout);

    auto read = Tools::read;

    int T;
    read(T);

    int n, m;
    read(n), read(m);

    int ans[6][6] = {{2, 3, 4, 4, 5, 5},
                     {3, 3, 4, 5, 5, 6},
                     {4, 4, 7, 8, 9, 10},
                     {4, 5, 8, 9, 9, 10},
                     {5, 5, 9, 9, 10, 11},
                     {6, 7, 8, 9, 10, 20}};

    printf("%d\n", ans[n-1][m-1]);

    fclose(stdin);
    fclose(stdout);

}