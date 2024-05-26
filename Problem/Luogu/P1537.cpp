//
// Created by kibi on 2021/9/6.
//
#include <bits/stdc++.h>
using namespace std;
int n1,n2,n3,n4,n5,n6,s,i,a[7];
int main(){
    while(true){
        scanf("%d %d %d %d %d %d", &n1, &n2, &n3, &n4, &n5, &n6);
        if((!n1)&&(!n2)&&(!n3)&&(!n4)&&(!n5)&&(!n6)){
            return 0;
        }
        i++;
        printf("Collection #%d:\n", i);
        s = 0;
        s += n1+n2*2+n3*3+n4*4+n5*5+n6*6;
        if(s%2){
            printf("Can't be divided.\n\n");
            continue;
        }
        a[1] = n1;
        a[2] = n2;
        a[3] = n3;
        a[4] = n4;
        a[5] = n5;
        a[6] = n6;
        int f[60006] = {};
        //        for(int i = 1; i <= 60000; i++){
        //            f[i] = 0;
        //        }
        f[0] = 1;
        for(int i = 1; i <= 6; i++){
            for(int j = a[i]; j > 0; j/=2){
                int t = j/2+j%2;
                int tt = t*i*2;
                for(int k = s; k >= tt; k--){
                    if(f[k-tt]){
                        f[k] = 1;
                    }
                }
            }
        }
        if(f[s]){
            printf("Can be divided.\n\n");
        }else{
            printf("Can't be divided.\n\n");
        }
    }
}