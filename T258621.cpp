//
// Created by kibi on 2022/8/7.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int n, a, e;
char c[200005];

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &n, &a, &e);
        int s = 0;
        scanf("%s", c+1);
        for(int i = 1; i <= 2*n; i++){
            s += c[i]=='A';
        }
        if(s-e>a||e-s>a||e<fabs(a-s)){
            printf("-1\n");
        }else{
            if(e > s){
                int y = e-s;
                int A = a-y;
                int u = 0;
                if(A%2==0){
                    u = A/2;
                }else{
                    printf("-1\n");
                    continue ;
                }
                y += u;
                for(int i = 1; i <= 2*n; i++){
                    if(c[i]=='A'&&u==0){
                        printf("B");
                    }else if(y&&c[i]=='B'){
                        printf("A");
                        y--;
                    }else if(u&&c[i]=='A'){
                        printf("A");
                        u--;
                    }
                }
                printf("\n");
            }else{
                int y = s-e;
                int A = a-y;
                int u = 0;
                if(A%2==0){
                    u = A/2;
                }else{
                    printf("-1\n");
                    continue ;
                }
                y += u;
                for(int i = 1; i <= 2*n; i++){
                    if(c[i]=='A'&&y){
                        y--;
                        printf("A");
                    }else if(c[i]=='A'){
                        printf("B");
                    }else if(c[i]=='B'&&u){
                        u--;
                        printf("A");
                    }else{
                        printf("B");
                    }
                }
                printf("\n");
            }
        }


    }
}