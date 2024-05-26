//
// Created by kibi on 2022/9/10.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int main(){
    scanf("%d", &T);
    while(T--){
        int r = 0, p = 0;
        bool flag = true;
        while(flag){
            printf("? %d\n", p);
            p+=2;
            int tem;
            scanf("%d", &tem);
            if(tem == -1){
                return 0;
            }
            flag = tem;
        }
        p -= 2;
        if(p == 0){
            int t = 0;
            while(!t){
                printf("? %d\n", p);
                p+=2;
                scanf("%d", &t);
            }
            t-=2;
            printf("? %d", p-1);
            scanf("%d", &t);
            if(t){
                p--;
            }
            flag = true;
            while(flag){
                printf("? %d\n", p);
                p+=2;
                int tem;
                scanf("%d", &tem);
                if(tem == -1){
                    return 0;
                }
                flag = tem;
            }
            p-=2;
        }
        printf("? %d\n", p-1);
        int tem;
        scanf("%d", &tem);
        if(tem){
            p++;
        }
        r = p;
        while(!flag){
            printf("? %d\n", p);
            p+=2;
            int tem;
            scanf("%d", &tem);
            if(tem == -1){
                return 0;
            }
            flag = tem;
        }
        p-=2;
        printf("? %d\n", p-1);
        scanf("%d", &tem);
        if(!tem){
            p++;
        }
        int t = p-r;
        t = ((t+1)*(t+1)+t*t)/2;
        t -= r-2;
        printf("! %d\n", t);
    }
}