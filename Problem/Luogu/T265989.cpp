//
// Created by kibi on 22-8-20.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, a[2000005];
long long mx, mn = 1e9;

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        long long t;
        scanf("%lld", &t);
        mx = max(mx, t);
        mn = min(mn, t);
    }
//    for(int i = 1; i <= m; i++){
//        if(mx<0){
//            if(max(2, mx/2-mx)>max(mn-mn*2, 2)){
//                if(2 > mx/2-mx){
//                    mx += 2;
//                }else{
//                    mx/=2;
//                }
//            }else{
//                if(2 > mn-mn*2){
//                    mn -= 2;
//                }else{
//                    mn *= 2;
//                }
//            }
//        }else{
//            if(max(2, mx*2-mx)>max(2, mn-mn/2)){
//                if(2 > mx*2-mx){
//                    mx += 2;
//                }else{
//                    mx = mx*2;
//                }
//            }else{
//                if(2 > mn-mn/2){
//                    mn -= 2;
//                }else{
//                    mn = mn/2;
//                }
//            }
//        }
//    }
    if(fabs(mx) >= fabs(mn)){
        if(mx>=2){
            mx = mx*(long long)pow(2,m);
        }else{
            mx = (mx+2)*(long long)pow(2,m-1);
        }
    }else{
        if(mn <= -2){
            mn = mn*(long long)pow(2, m);
        }else{
            mn = (mn-2)*(long long)pow(2, m-1);
        }
    }
    printf("%lld", mx-mn);
}