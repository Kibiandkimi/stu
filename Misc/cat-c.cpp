//
// Created by kibi on 2021/11/6.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    scanf("%d", &n);
    printf("%d\n", n);
    for(int i = 1; i <= n; i++){
        printf("1 %d\n", i);
        printf("%d ", n-1);
        for(int j = 1; j <= n; j++){
            if(i!=j){
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}