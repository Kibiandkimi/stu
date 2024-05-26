//
// Created by kibi on 2022/7/17.
//
//45pts(100pts在下面)
//#include <bits/stdc++.h>
//using namespace std;
//int n, m, k;
//bool a[100005];
//int main(){
//    scanf("%d %d %d", &n, &m, &k);
//    if(k == 1 || n==m){
//        for(int i = 1; i <= n; i++){
//            if(i%2){
//                printf("l");
//            }else{
//                printf("r");
//            }
//        }
//        return 0;
//    }else if(k == 2){
//        for(int i = 1; i <= m; i++){
//            if(i%2){
//                printf("l");
//            }else{
//                printf("r");
//            }
//        }
//        for(int i = m+1; i <= n; i++){
//            if((i-m) % 3){
//                printf("l");
//            }else{
//                printf("r");
//            }
//        }
//        return 0;
//    }
//    for(int i = 1, j = 0; i <= n; i++){
//        if(j==m){
//            printf("ll");
//            j = 0;
//            i += 1;
//        }else{
//            if(i%2){
//                printf("l");
//            }else{
//                printf("r");
//            }
//            j++;
//        }
//    }
//}
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int main(){
    scanf("%d %d %d", &n, &m, &k);
    if(k == 1 || n==m){
        for(int i = 1; i <= n; i++){
            if(i%2){
                printf("l");
            }else{
                printf("r");
            }
        }
        return 0;
    }else if(k == 2){
        for(int i = 1; i <= m-2; i++){
            if(i%2){
                printf("l");
            }else{
                printf("r");
            }
        }
        for(int i = (m-2)+1; i <= n; i++){
            if((i-(m-2)) % 3){
                printf("l");
            }else{
                printf("r");
            }
        }
        return 0;
    }
    for(int i = 1, j = 0; i <= n; i++){
        if(j==m){
            if(i==n){
                printf("l");
                return 0;
            }
            printf("ll");
            j = 0;
            i += 1;
        }else{
            if(i%2){
                printf("l");
            }else{
                printf("r");
            }
            j++;
        }
    }
}