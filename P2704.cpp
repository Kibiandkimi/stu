//
// Created by kibi on 22-8-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, a[105], num[3005], d[3005][3005][3];
//int cnt;
char x[15];

int f(int s){
    int tot = 0;
    while(s){
        if(s&1){
            tot++;
        }
        s>>=1;
    }
    return tot;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%s", x+1);
        for(int j = 1; j <= m; j++){
            a[i] <<= 1;
            a[i] += (x[j]=='H'?1:0);
        }
    }
    for(int i = 0; i <= (1<<m); i++){
        num[i] = f(i);
    }
    for(int s = 0; s < (1<<m); s++){
        if(!((s&a[1])||(s&(s<<1))||(s&(s<<2)))){
            d[0][s][0] = num[s];
        }
    }
    for(int l = 0; l < (1<<m); l++){
        for(int s = 0; s < (1<<m); s++){
            if(!((l&s)||(l&a[1])||(s&a[2])||(l&(l<<1))||(l&(l<<2))||(s&(s<<1))||(s&(s<<2)))){
                d[l][s][1] = num[s]+num[l];
            }
        }
    }
    for(int i = 3; i <= n; i++){
        for(int l = 0; l < (1<<m); l++){
            if((l&(a[i-1]))||(l&(l<<1))||(l&(l<<2))){
                continue;
            }
            for(int s = 0; s < (1<<m); s++){
                if((s&a[i])||(l&s)||(s&(s<<1))||(s&(s<<2))){
                    continue;
                }
                for(int fl = 0; fl < (1<<m); fl++){
                    if((fl&l)||(fl&s)||(fl&a[i-2])||(fl&(fl<<1))||(fl&(fl<<2))){
                        continue;
                    }
                    d[l][s][(i-1)%3] = max(d[l][s][(i-1)%3], d[fl][l][(i-2)%3]+num[s]);
                }
            }
        }
    }
    int ans = 0;
    for(int l = 0; l < (1<<m); l++){
        for(int s = 0; s < (1<<m); s++){
            ans = max(ans, d[l][s][(n-1)%3]);
        }
    }
    printf("%d", ans);
}