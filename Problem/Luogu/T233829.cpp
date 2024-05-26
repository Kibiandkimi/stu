//
// Created by kibi on 22-8-20.
//
#include <bits/stdc++.h>
using namespace std;
int a[10];
int z[505];
int cnt;
long long num1, num2;
bool flag, ff;
int l1, l2;

int q(){
    for(int i = 2; i <= 505; i++){
        for(int j = 1; j*j<=i; j++){
            if(i%j==0){
                flag = true;
                j = i;
            }
        }
        if(!flag){
            z[++cnt] = i;
        }
        flag = false;
    }
}

//int q

int main(){
    q();
    scanf("%d %d %d %d %d %d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], &a[9]);
    for(int i = 9; i >= 0; i--){
        if(a[i]==0){
            continue;
        }
        if(a[i]%2==0){
            if(l1<=l2) {
                int sj = a[i] / 2;
                for (int j = 1; j <= sj; j++) {
                    printf("%d", i);
                }
                a[i] /= 2;
            }else{
                if(flag){
                    int sj = (a[i]-2)/2;
                    for (int j = 1; j <= sj; j++) {
                        printf("%d", i);
                    }
                    a[i] -= sj;
                    l2 += 2;
                }else{
                    int sj = (a[i]+2)/2;
                    for (int j = 1; j <= sj; j++) {
                        printf("%d", i);
                    }
                    a[i] -= sj;
                    l1 += 2;
                }
                if(l1 > l2){
                    flag = true;
                }else if(l1 < l2){
                    flag = false;
                }else{
                    flag = true;
                }
            }
        }else{
            if(flag){
                int sj = a[i]/2;
                l2++;
                for(int j = 1; j <= sj; j++) {
                    printf("%d", i);
                }
                a[i] -= sj;
            }else{
                int sj = a[i]/2 + 1;
                l1++;
                for(int j = 1; j <= sj; j++){
                    printf("%d", i);
                }
                a[i] -= sj;
            }
            if(l1 > l2){
                flag = true;
            }else if(l1 < l2){
                flag = false;
            }else{
                flag = true;
            }
        }
    }
    printf("\n");
    for(int i = 9; i >= 0; i--){
        while(a[i]--){
            printf("%d", i);
        }
    }
}