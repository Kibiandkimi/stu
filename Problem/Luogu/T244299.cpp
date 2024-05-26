//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
long long n, m;
int main(){
    scanf("%lld %lld", &n, &m);
    //    for(int nn = 1; nn <= n; nn++) {
    //        long long ans = 0;
    ////        long long ti = nn*(nn+1)/2;
    ////        long long tj = ti*(ti+1)/2;
    ////        ans = ti*tj*tj%m;
    //        ans = nn*(nn+1)*(nn+2)*(8*nn*nn+11*nn+1)/120;
    //        for (int i = 1; i <= nn; i++) {
    ////            ans = (ans + (i+1)*(2*i+1)*i*i/6)%m;
    //            for (int j = 1; j <= i; j++) {
    ////                ans = (ans + i*j*j) % m;
    ////                for (int k = 1; k <= j; k++) {
    //////                    ans = (ans + i * j) % m;
    ////
    ////                }
    //                long long t = 1;
    //                for (int p = 1; p <= j; p++) {
    //                    if (p % 2) {
    //                        t = (t * p) % m;
    //                    } else {
    //                        t = (t * p * p) % m;
    //                    }
    //                }
    //                ans = (ans + (j*(j+1)/2)*t) % m;
    //            }
    //        }
    //        printf("%lld\n", ans);
    //    }

    //    for(int nn = 1; nn <= n; nn++) {
    //        ans = 0;
    //        for (int i = 1; i <= nn; i++) {
    //            for (int j = 1; j <= i; j++) {
    //                for (int k = 1; k <= j; k++) {
    ////                    ans = (ans + i * j) % m;
    ////                    long long t = 0;
    ////                    for (int p = 1; p <= j; p++) {
    ////                        if (p % 2) {
    ////                            t = (t + p) % m;
    ////                        } else {
    ////                            t = (t + p * p) % m;
    ////                        }
    ////                    }
    ////                    ans = (ans + k*t) % m;
    ////                    for(int l = 1; l <= k; l++){
    ////                        ans =
    ////                    }
    //                }
    //            }
    //        }
    //        printf("%lld\n", ans);
    //    }


    for(int nn = 1; nn <= n; nn++) {
        long long ans = 0;
        ans = (nn*(nn+1)*(nn+2)*(8*nn*nn+11*nn+1)/120)%m;
        for (int i = 1; i <= nn; i++) {
            long long t = ((i+1)*i/2)%m;
            for(int p = i; p >= 1; p--){
                if(p%2){
                    t = (p*t+(p-1)*p/2)%m;
                }else{
                    t = (p*p*t+(p-1)*p/2)%m;
                }
            }
            ans = (ans + t)%m;
        }
        printf("%lld\n", ans);
    }

}