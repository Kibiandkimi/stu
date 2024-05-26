//
// Created by kibi on 22-9-22.
//
//12pts
#include <bits/stdc++.h>
using namespace std;
int n, a[10005], d[10005], now[10005];
bool visD[10005], visN[10005];
long long ans = 1e18;

void read(int &x);
void f(int u);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        d[i] = a[i] - a[i-1];
    }
    now[1] = d[1], visN[1] = visD[1] = true;
    f(2);
    printf("%lld", ans);
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

void f(int u){
    if(u == n){
        int p;
        for(int i = 1; i <= n; i++){
            if(!visD[i]){
                p = i;
                break;
            }
        }
        for(int i = 1; i <= n; i++){
            if(!visN[i]){
                now[i] = d[p];
                //                p = i;
                break;
            }
        }
        static long long tem[10005];
        tem[0] = 0;
        long long tans = 0, t2 = 0;
        for(int i = 1; i <= n; i++){
            tem[i] = tem[i-1] + now[i];
            tans += tem[i] * tem[i];
            t2 += tem[i];
        }
        tans *= n;
        t2 = t2 * t2;
        ans = min(ans, tans - t2);
        return ;
    }
    for(int i = 1; i <= n; i++){
        if(visD[i]){
            continue;
        }
        visD[i] = true;
        for(int j = 1; j <= n; j++){
            if(!visN[j]){
                visN[j] = true;
                now[j] = d[i];
                f(u+1);
                //                now[j] = 0;
                visN[j] = false;
            }
        }
        visD[i] = false;
    }
}