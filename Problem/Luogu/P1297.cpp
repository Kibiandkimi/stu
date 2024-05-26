//
// Created by kibi on 2021/9/29.
//
#include <bits/stdc++.h>
using namespace std;
int a[10000005];
double ans;
int n,A,B,C;
int main(){
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    for (int i = 2; i <= n; i++)
        a[i] = ((long long) a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;

    ans += 1.0/max(a[1],a[n]);
    for(int i = 2; i <= n; i++){
        ans += 1.0/max(a[i], a[i-1]);
    }
    printf("%.3lf", ans);
}