//
// Created by kibi on 22-8-14.
//
#include <bits/stdc++.h>
using namespace std;
int n;

int main(){
    scanf("%d", &n);
    printf("%d\n", (n+n/2)+(n%2));
    int d = n/2+(n%2);
    for(int j = 1; j <= n; j++){
        for(int i = 1; i <= n; i++){
            printf("2 ");
            printf("%d ", i);
            if(j>d){
                printf("%d %d ", i, -(n+j-d));
            }else {
                printf("%d %d ", i, n + j);
            }
            printf("%d\n", j);
        }
    }
}