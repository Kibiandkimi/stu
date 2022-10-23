//
// Created by kibi on 2022/10/22.
//
#include <bits/stdc++.h>
using namespace std;

void read(long long &x);

int main(){
    long long n;
    read(n);
    queue<long long> q;
    static const int end = 123804765, nxt[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    static unordered_map<long long, long long> y;
    if(n == end){
        printf("0");
        return 0;
    }
    q.push(n);
    y[n] = 0;
    while(!y[end]){
        static long long u, tem;
        tem = u = q.front();
        q.pop();
        static int c[3][3], x0, y0;
        for(int i = 2; i >= 0; --i){
            for(int j = 2; j >= 0; --j){
                c[i][j] = (int)(tem%10), tem = tem/10;
                !c[i][j]?x0=i,y0=j:0;
            }
        }
        for(auto i : nxt){
            static int nx, ny, now;
            nx = x0 + i[0], ny = y0 + i[1];
            if(nx > 2 || ny > 2 || nx < 0 || ny < 0){
                continue;
            }
            swap(c[nx][ny], c[x0][y0]);
            now = 0;
            for(auto & j : c){
                for(int k : j){
                    now = now * 10 + k;
                }
            }
            if(!y[now]){
                y[now] = y[u] + 1;
                q.push(now);
            }
            swap(c[nx][ny], c[x0][y0]);
        }
    }
    printf("%lld", y[end]);
}

void read(long long &x){
    long long s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while(c != EOF){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s;
}