//
// Created by kibi on 2022/8/7.
//
#include <bits/stdc++.h>
using namespace std;
int T, a[10];
bool flag[20];

int main(){
    freopen("qi.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        memset(flag, 0, sizeof flag);
        int r = -1;
        bool wd = false;
        bool h = false;
        for(int i = 1; i <= 4; i++){
            scanf("%d", &a[i]);
            if(flag[a[i]]){
                if(r!=-1){
                    if(r == a[i]){
                        h = true;
                    }else {
                        wd = true;
                    }
                }
                r = a[i];
            }
            flag[a[i]] = true;
        }
        if(wd){
            printf("0\n");
        }else if(r!=-1){
            flag[r] = false;
            if(h){
                flag[r] = true;
            }
            bool t = false;
            for (int i = 1; i <= 8; i++) {
                if(flag[i-1]+flag[i]+flag[i+1]==2){
                    t = true;
                }
            }
            if (t) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }else{
            bool t = false;
            for (int i = 1; i <= 8; i++) {
                if (flag[i - 1] == flag[i] && flag[i] == flag[i + 1] && flag[i]) {
                    t = true;
                }
            }
            if (t) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }

    }
    fclose(stdout);
}