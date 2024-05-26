//
// Created by kibi on 23-11-1.
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

    class Segment{
    public:
        int l, r;

        static bool cmp(const Segment &a, const Segment &b){
            return a.r == b.r ? a.l < b.l : a.r > b.r;
        }
    };

    int n, m;
    read(n), read(m);

    Segment seg[n];
    for(auto &i : seg){
        read(i.l), read(i.r);
        //        i.r--;
    }

    sort(seg, seg + n, Segment::cmp);

    const int mxv = 500000;

    static int jump[mxv + 2][20], sum[mxv + 1];
    memset(sum, 0, sizeof sum);
    for(int i = mxv, now = 0; i >= 0; i--){
        while(seg[now].l > i){
            now++;
        }
        if(seg[now].r < i){
            jump[i][0] = i;
            sum[i] = sum[i + 1] + 1;
        }else{
            jump[i][0] = seg[now].r;
            sum[i] = sum[i + 1];
        }
    }

    for(auto &i : jump[mxv + 1]){
        i = mxv;
    }
    for(int i = 1; i < 20; i++){
        for(int j = 0; j <= mxv; j++){
            jump[j][i] = jump[jump[j][i - 1]][i - 1];
        }
    }

    while(m--){
        int l, r;
        read(l), read(r);
        //        r--;
        if(sum[l] != sum[r]){
            printf("-1\n");
            continue;
        }
        int ans = 0, now = l;
        for(int i = 19; i >= 0; i--){
            if(jump[now][i] < r){
                ans += (1 << i);
                now = jump[now][i];
            }
        }
        if(jump[now][0] < r){
            printf("-1\n");
            continue;
        }
        ans++;
        printf("%d\n", ans);
    }

}