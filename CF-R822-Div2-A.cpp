//
// Created by kibi on 2022/9/23.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int n, a[305], ans = 1e9;

void read(int &x);

int main(){
    read(T);
    while(T--){
        read(n);
        for(int i = 1; i <= n; i++){
            read(a[i]);
        }
        for(int i = 1; i <= n; i++){
            for(int j = i+1; j <= n; j++){
                for(int k = j+1; k <= n; k++){
                    int mn = min(min(a[i], a[j]), a[k]), mx = max(max(a[i], a[j]), a[k]);
                    int mid = a[i]+a[j]+a[k] - mn - mx;
                    ans = min(ans, mid-mn + mx-mid);
                }
            }
        }
        printf("%d\n", ans);
        ans = 1e9;
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}