//
// Created by kibi on 2021/11/6.
//
#include <bits/stdc++.h>
using namespace std;
int n, l, r, s, sl, sr;
int mod = 1e9+7;
int a[3005];
int vis[3005];
//int tr[12005];
//int lowbit(int x){
//    return x&-x;
//}
//void add(int x){
//    for(int i = x; i <= 5005; i += lowbit(x)){
//        tr[i] = (tr[i]+1)%((int)(1e9));
//    }
//}
//int query(int x){
//    int ts = 0;
//    for(int i = x; i != 0; i -= lowbit(x)){
//        ts += tr[i];
//    }
//    return (ts%(int)(1e9));
//}
int f(int x, int m){
    int ss = 0;
    if(x>=sl&&x!=0){
        ss++;
    }
    for(int i = m; i <= n; i++){

        if(x+a[i]<=(sr)){
            vis[a[i]] = true;
            ss = (ss+f(x+a[i], i+1))%mod;
            vis[a[i]] = false;
        }
        while(a[i+1]==a[i]){
            i++;
        }
    }
    return ss%mod;
}
int main(){
    scanf("%d %d %d", &n, &l, &r);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        s += a[i];
    }
    sl = max(s - r, l);
    sr = min(s - l, r);
    sort(a+1, a+1+n);
    //    for(int i = 1; i <= n; i++){
    //        add(a[i]);
    //    }
    cout << f(0, 1);
    return 0;
}