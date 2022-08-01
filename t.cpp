//
// Created by kibi on 2021/11/7.
//
#include <bits/stdc++.h>
using namespace std;
int n;
//int a
int main(){
    scanf("%d", &n);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            printf("0000");
        }
        printf("\n");
        for(int j = 1; j <= n; j++){
            printf("0110");
        }
        printf("\n");
        for(int j = 1; j <= n; j++){
            printf("0110");
        }
        printf("\n");
        for(int j = 1; j <= n; j++){
            printf("0000");
        }
        printf("\n");
    }
}