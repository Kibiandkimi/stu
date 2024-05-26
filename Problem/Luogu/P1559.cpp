//
// Created by kibi on 2022/5/28.
//
//91pts暴搜，100pts状压
//#include <bits/stdc++.h>
//using namespace std;
//long long n, p[25][25];
//long long mx[25], ans;
//bool vis[25];
//void f(long long t, long long x){
//    if(t > n){
//        ans = max(ans, x);
//        return;
//    }
//    long long s = 0;
//    for(int i = t; i <= n; i++){
//        s += mx[i];
//    }
//    if(x + s <= ans){
//        return;
//    }
//    for(int i = 1; i <= n; i++){
//        if(!vis[i]){
//            vis[i] = true;
//            f(t+1, x+p[t][i]);
//            vis[i] = false;
//        }
//    }
//}
//int main(){
//    scanf("%lld", &n);
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= n; j++){
//            scanf("%lld", &p[i][j]);
//        }
//    }
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= n; j++){
//            int t;
//            scanf("%lld", &t);
//            p[j][i] *= t;
//        }
//    }
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= n; j++){
//            mx[i] = max(mx[i], p[i][j]);
//        }
//    }
//
//    f(1, 0);
//    printf("%lld", ans);
//    return 0;
//}
#include <bits/stdc++.h>
using namespace std;
long long n, p[25][25];
long long mx[25], qz[25], ans;
long long mem[2000005], now;
bool vis[2000005];
int nxt[25], pre[25], head;
long long f(long long t, long long x) {
    if (t > n) {
        ans = max(ans, x);
        return 0;
    }
    //    long long s = qz[n] - qz[t - 1];
    //    if (x + s <= ans) {
    //        return 0;
    //    }
    long long mxs = 0;
    for (int i = nxt[0]; i <= n; i = nxt[i]) {
        nxt[pre[i]] = nxt[i], pre[nxt[i]] = pre[i];
        now -= 1 << (i - 1);
        if (vis[now]) {
            ans = max(ans, x + mem[now] + p[t][i]);
        } else {
            mem[now] = f(t + 1, x + p[t][i]);
            vis[now] = true;
        }
        mxs = max(mxs, mem[now] + p[t][i]);
        nxt[pre[i]] = i, pre[nxt[i]] = i;
        now += 1 << (i - 1);
    }
    return mxs;
}
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lld", &p[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long t;
            scanf("%lld", &t);
            p[j][i] *= t;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mx[i] = max(mx[i], p[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        nxt[i] = i + 1, pre[i] = i - 1;
        qz[i] = qz[i - 1] + mx[i];
    }
    nxt[0] = 1;
    now = (1 << n) - 1;
    f(1, 0);
    printf("%lld", ans);
    return 0;
}