//
// Created by kibi on 2022/9/10.
//
#include <bits/stdc++.h>
using namespace std;
int d[1000005];
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++){
        scanf("%d", &d[i]);
    }
    if(n>=10) {
        for (int i = 1; i <= n; i++) {
            printf("0 %d\n", i);
        }
    }else{

    }
}