//
// Created by kibi on 2022/8/6.
//
#include <bits/stdc++.h>
using namespace std;
int n, k, q;
int a[100005];
int que[10004][4];
int b[10005][2];
int mn = 1e9;
//bool flag[10005];

int f1(int num){
    int i = que[num][0], j = que[num][1], x = que[num][2], y = que[num][3];
    int ans = 1e9;
    int r1 = b[i][1], r0 = b[i][0];
    bool flag = false;
    if(b[i][0]){
        if(b[i][0]<=x){
            b[i][1] = min(b[i][1], x);
        }else{
            flag = true;
        }
    }else{
        b[i][0] = 1;
        b[i][1] = x;
    }

    if(!flag) {
        if (num < q) {
            ans = min(ans, f1(num + 1));
        } else {
            int t = 0;
            for (int i = 1; i <= k; i++) {
                int tt = 1e9;
                for (int j = b[i][0]; j <= b[i][1]; j++){
                    tt = min(tt, a[j]);
                }
                if(!b[i][0]){
                    tt = mn;
                }
                t += tt;
            }
            ans = min(ans, t);
        }
        b[i][0] = r0, b[i][1] = r1;
    }

    r0 = b[j][0], r1 = b[j][1];
    if(b[j][0]){
        if(b[j][1]<n-y+1){
            return ans;
        }else{
            b[j][0] = max(b[j][0], n-y+1);
        }
    }else{
        b[j][0] = n-y+1;
        b[j][1] = n;
    }

    if (num < q) {
        ans = min(ans, f1(num + 1));
    } else {
        int t = 0;
        for (int i = 1; i <= k; i++) {
            int tt = 1e9;
            for (int j = b[i][0]; j <= b[i][1]; j++){
                tt = min(tt, a[j]);
            }
            if(!b[i][0]){
                tt = mn;
            }
            t += tt;
        }
        ans = min(ans, t);
    }
    b[j][0] = r0, b[j][1] = r1;
    return ans;

}

int main(){
    //    int mn = 1e9;
    scanf("%d %d %d", &n, &k, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        mn = min(a[i], mn);
    }
    for(int i = 1; i <= q; i++){
        scanf("%d %d %d %d", &que[i][0], &que[i][1], &que[i][2], &que[i][3]);
    }
    printf("%d", f1(1));

}