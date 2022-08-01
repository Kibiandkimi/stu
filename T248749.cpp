//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
using namespace std;
int S, T;
int b[25005], s[70005];
bool ans[25005];
int h[70005];
bool r[70005];
bool now[70005];

int main(){
    scanf("%d %d", &S, &T);
    while(T--){
        memset(now, 0, sizeof now);
        memset(s, 0, sizeof s);
        memset(h, 0, sizeof h);
        memset(ans, 0, sizeof ans);
        memset(r, 0, sizeof r);
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        int mx = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &b[i]);
            s[b[i]]++;
            mx = max(mx, b[i]);
        }
        int t = b[1];
        for(int i = mx; i>=0 && y>0; i--){
            if(s[i]>0&&s[i]%2==0){
                r[i] = true;
                y--;
            }
        }
        for(int i = mx; i>=0 && y>0; i--){
            if(s[i]-(int)r[i]>0){
                //                r[i] = false;
                int tt = min(y, s[i]-(int)(t==i)-(int)r[i]);
                h[i] += tt;
                y -= tt;
            }
        }
        now[b[1]] = true;
        s[b[1]]--;
        for(int i = 2; i <= n; i++){
            if((r[b[i]] && now[b[i]])){
                ans[i-1] = true;
                r[b[i]] = false;
            }else if(h[b[i]]&&h[b[i]]==(s[b[i]]-r[b[i]])){
                ans[i-1] = true;
                h[b[i]]--;
                now[b[i]] = true;
            }else{
                ans[i-1] = false;
                now[b[i]] ^= 1;
            }
            s[b[i]]--;
        }


        bool flag = false;
        for(int i = mx; i >= 0; i--){
            if(now[i]){
                flag = true;
                printf("1");
            }else if(flag){
                printf("0");
            }
        }
        if(!flag){
            printf("0");
        }
        printf("\n");
        for(int i = 1; i < n; i++){
            if(ans[i]){
                printf("|");
            }else{
                printf("^");
            }
        }
        printf("\n");
    }
}