//
// Created by kibi on 2021/11/14.
//
#include <bits/stdc++.h>
using namespace std;
long long T, n;
int t[1000005];
//vector<int> z;
//vector<int> c[1000005];
//void f(int x, int p){
//
//}
int main(){
    /*
    for(int i = 2; i <= 1000; i++){
        bool flag = true;
        for(int j = 2; j * j <= i; j++){
            if(i%j==0){
                flag = false;
                break;
            }
        }
        if(flag){
            z.push_back(i);
        }
    }
    */
    scanf("%lld", &T);
    while(T--){
        scanf("%lld", &n);
        //        int sa = 0;
        if(n%3==0){
            printf("%lld\n", (long long)pow((n/3), 3));
            continue;
        }
        vector<long long> tt;
        for(int i = 1; i * i <= n; i++){
            if(n%i==0){
                t[i] = n;
                //                sa++;
                tt.push_back(i);
            }
        }
        int sa = tt.size();
        for(int i = sa-1; i >= 0; i--){
            tt.push_back(n/tt[i]);
            t[n/tt[i]] = n;
            //            sa++;
        }
        sa = tt.size();
        long long mx = -1;
        for(int i = 0; i < sa; i++){
            for(int j = 0; j < sa; j++){
                if(t[n-tt[i]-tt[j]]!=n){
                    continue;
                }else{
                    mx = max(mx, (long long)(tt[i]*tt[j]*(n-tt[i]-tt[j])));
                }
            }
        }
        printf("%lld\n", mx);
    }

}