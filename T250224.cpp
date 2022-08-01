//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
using namespace std;
int S, T;
int main(){
    scanf("%d %d", &S, &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        int s = (n/2+n%2)*(m/2+m%2);
        double t;
        if(S == 1){
            t = 0;
            for(int i = 1; i <= n; i+=2){
                for(int j = 1; j <= m; j+=2){
                    bool f1 = (i-1)>(n-i), f2 = (j-1)>(m-j);
                    t += sqrt((i-(f1?1:n))*(i-(f1?1:n))+(j-(f2?1:m)*(j-(f2?1:m))));
                }
            }
        }
        printf("%d %lf\n", n*m-s, t);
    }
}