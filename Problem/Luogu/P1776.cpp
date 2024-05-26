//
// Created by kibi on 2021/8/31.
//
#include <bits/stdc++.h>
using namespace std;
int n,W,head,tail,ans,dp[40005],q1[40005],q2[40005];
int main(){
    scanf("%d %d", &n, &W);
    for(int i = 1; i <= n; i++){
        int v,w,c;
        scanf("%d %d %d", &v, &w, &c);
        if(!w){
            ans += v*c;
        }
        c = min(c,W/w);
        for(int d = 0; d < w; d++){
            head = tail = 0;
            int k = (W-d)/w;
            for(int j = 0; j <= k; j++){
                while(head<tail&&dp[d+j*w]-j*v>=q2[tail-1]){
                    tail--;
                }
                q1[tail] = j;
                q2[tail++] = dp[d+j*w]-j*v;
                while(head < tail&&q1[head] < j-c){
                    head++;
                }
                dp[d+j*w] = max(q2[head]+j*v, dp[d+j*w]);
            }
        }
    }
    cout << ans+dp[W];
    return 0;
}

/*

#include <bits/stdc++.h>
using namespace std;

const int W = 40000;

void read(int&);

int main(){
    static int f[W + 5];
    int n, w, ans = 0;
    read(n), read(w);
    for(int i = 1; i <= n; i++){
        int _v, _w, _m;
        read(_v), read(_w), read(_m);
        if(_v < 0){
            continue;
        }
        else if(_w == 0){
            ans += _v*_m;
            continue;
        }
        int k = w/_w;
        _m = min(_m, k);
        for(int d = 0; d < _w; d++){
            static int head, tail, q1[W + 5], q2[W + 5];
            head = 0;
            tail = -1;
            for(int j = 0; j <= k; j++){
                while(head <= tail && f[d+j*_w] - j*_v >= q2[tail]){
                    tail--;
                }
                q1[++tail] = j;
                q2[tail] = f[d+j*_w] - j*_v;
                while(head<=tail && q1[head] < j-_m){
                    head++;
                }
                f[d+j*_w] = max(f[d+j*_w], q2[head] + j*_v);
            }
        }
    }
    printf("%d\n", ans + f[w]);
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

*/