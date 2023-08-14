//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 500000, M = 500000;

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

    class Node{
    public:
        int id, l, r;
    };

    auto read = Tools::read;

    int n, m, q;
    read(n), read(m), read(q);

    static Node node[M + 5];

    for(int i = 1; i <= m; i++){
        int l, r;
        read(l), read(r);
        node[i] = {i, l, r};
    }

    while(q--){
        int l, r;
        read(l), read(r);
        static int flag[N + 5];

        for(int i = 1; i <= m; i++){
            if(node[i].l >= l && node[i].r <= r){
                flag[node[i].l]++;
                flag[node[i].r+1]--;
            }
        }

        bool _flag = true;
        int now = 0;
        for(int i = l; i <= r; i++){
            now += flag[i];
            flag[i] = 0;
            if(now <= 0){
                _flag = false;
            }
        }

        flag[r+1] = 0;

        if(_flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }

    }

}