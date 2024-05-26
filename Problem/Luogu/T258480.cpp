//
// Created by kibi on 2022/8/7.
//
//#include <bits/stdc++.h>
//using namespace std;
//long long T, s, m;
//long long a[65], mx;
//long long ind[65];
//long long o[1000005];
//int cnt = 1;
//
////long long pow(long long x, int t){
////    if(t == 0){
////        return 1;
////    }
////    long long ans = x;
////    while(--t){
////        ans = ans*x;
////    }
////    return ans;
////}
//
//int main(){
//    scanf("%lld", &T);
//    ind[0] = 1;
//    for(int i = 1; i <= 60; i++){
////        ind[i] = pow(2, i);
//        ind[i] = ind[i-1]*2;
//    }
//    while(T--){
//        scanf("%lld %lld", &s, &m);
//        mx = 0;
//        for(int i = 60; i >= 0; i--){
//            long long t = s/ind[i];
//            if(t>=2){
//                t -= t%2;
//                a[i] = t;
//                s -= t*ind[i];
//                mx = max(mx, a[i]);
//            }else{
//                a[i] = 0;
//            }
//        }
//        if(mx <= m && s==0){
//            int st = cnt;
//            bool flag = true;
//            while(flag){
//                long long res = 0;
//                flag = false;
////                bool st = false;
//                for(int i = 60; i >= 0; i--){
//                    if(a[i]){
//                        flag = true;
//                        res += ind[i];
//                        a[i]--;
//                    }
//                }
//                if(flag) {
//                    o[cnt++] = res;
//                }
//            }
//            printf("%d ", cnt-st);
//            for(int i = st; i < cnt; i++){
//                printf("%lld ", o[i]);
//            }
//
//        }else{
//            printf("-1");
//        }
//        printf("\n");
//    }
////cout << log2(1e18);
//}
#include <bits/stdc++.h>
using namespace std;
long long T;

int main(){
    scanf("%lld", &T);
    while(T--){
        long long s, m;
        scanf("%lld %lld", &s, &m);
        if(s%2==0&&m>=2){
            printf("2 %lld %lld\n", s/2, s/2);
        }else{
            printf("-1\n");
        }
    }
}