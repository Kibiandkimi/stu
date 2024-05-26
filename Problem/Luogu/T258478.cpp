//
// Created by kibi on 2022/8/7.
//
#include <bits/stdc++.h>
using namespace std;
int T;
char c[25];
//int s[]

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%s", c+1);
        int last = -1, num = 1;
        bool flag = false;
        for(int i = 1; i <= 17; i++){
            if(c[i]==last){
                num++;
            }else{
                last = c[i];
                num=1;
            }
            if(num == 4){
                flag = true;
            }
        }
        if(flag || c[2]=='X'&&c[1]=='D'){
            printf("Yes");
        }else{
            printf("No");
        }
        printf("\n");
    }
}