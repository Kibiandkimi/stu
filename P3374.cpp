//
// Created by kibi on 2021/8/5.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[500005],b[500005];
int lowbit(int x){ return x & -x;}
int update(int x, int v){
    while(x <= n){
        b[x] += v;
        x += lowbit(x);
    }
    return 0;
}
int query(int x){
    int res = 0;
    while(x > 0){
        res += b[x];
        x -= lowbit(x);
    }
    return res;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        update(i, a[i]);
    }
    for(int i = 1; i <= m; i++){
        int t1,t2,t3;
        scanf("%d %d %d", &t1, &t2, &t3);
        if(t1 == 1){
            update(t2, t3);
        }else{
            printf("%d\n", query(t3)-query(t2-1));
        }
    }

}