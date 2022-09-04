//
// Created by kibi on 22-9-4.
//
//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
int a, b;

int main(){
    scanf("%d %d", &a, &b);
    int c = b/a;
    double ans = (double)c/(double)b;
    //    cout << ans;
    printf("%.8lf", ans);
}