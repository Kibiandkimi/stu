//
// Created by kibi on 23-7-19.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 200000, K = 50;

void read(int&);

int main(){

    class LinkList{
    public:
        int head[K + 5], nxt[N + 5], to[N + 5], cnt, end[N + 5], sum[K + 5];
        void link_back(int _col, int x){
            sum[_col]++;
            to[++cnt] = x;
            if(!end[_col]){
                head[_col] = cnt;
                end[_col] = cnt;
                return;
            }
            nxt[end[_col]] = cnt;
            end[_col] = cnt;
        }

    };

    int n, k, p;
    static LinkList list;
    static int col[N+5], cos[N+5], pre[N+5] = {0};

    read(n), read(k), read(p);

    for(int i = 1; i <= n; i++){
        read(col[i]), read(cos[i]);
        list.link_back(col[i], i);
        if(cos[i] <= p){
            pre[i]++;
        }
        pre[i] += pre[i-1];
    }

    long long ans = 0;

    for(int i = 0; i < k; i++){
        for(int j = list.head[i]; list.nxt[j]; j = list.nxt[j]){
            static int s, cnt;
            if(j == list.head[i]){
                s = 1, cnt = 1;
            }
            if(pre[list.to[list.nxt[j]]] - pre[list.to[j]-1]){
                ans += s * (list.sum[i] - cnt);
                s = 0;
            }
            s++;
            cnt++;

        }
    }

    printf("%lld\n", ans);

}

void read(int &x){
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