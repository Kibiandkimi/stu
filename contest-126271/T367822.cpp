//
// Created by kibi on 23-8-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 100000;

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

    int n;
    read(n);

    static int p[N + 5];
    for(int i = 1; i <= n; i++){
        read(p[i]);
    }

    static int vis[N + 5], res = n;
    for(int i = 1; i <= n; i++){
        int now = i;
        while(!vis[now]){
            vis[now] = true;
            res--;
            now = p[now];
        }
        printf("%d ", res);
    }

}