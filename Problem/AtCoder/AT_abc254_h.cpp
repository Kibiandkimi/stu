//
// Created by kibi on 23-9-30.
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
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    priority_queue<int> a, b;
    for(int i = 1; i <= n; i++){
        int t;
        read(t);
        a.emplace(t);
    }
    for(int i = 1; i <= n; i++){
        int t;
        read(t);
        b.emplace(t);
    }

    static int ans;
    while(!a.empty()){
        int u = a.top(), v = b.top();
        if(u == v){
            a.pop();
            b.pop();
        }else if(u > v){
            ans++;
            u >>= 1;
            a.pop();
            a.emplace(u);
        }else{
            if(v & 1){
                printf("-1");
                return 0;
            }else{
                ans++;
                v >>= 1;
                b.pop();
                b.emplace(v);
            }
        }
    }

    printf("%d\n", ans);
}