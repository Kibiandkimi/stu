//
// Created by kibi on 2022/8/7.
//
#include <bits/stdc++.h>
using namespace std;
int n;
unsigned long long num[300050];
int cnt = 1;
map<pair<int, int>, int> a;
unsigned long long ans;

unsigned long long lose(unsigned long long r, unsigned long long b, unsigned long long c){
    if(r>=b){
        return 0;
    }
    return (min(c, b-r))*2;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        unsigned long long x, y, z;
        scanf("%llu %llu %llu", &x, &y, &z);
        //        int rs =
        if(!a[{x, y}]){
            a[{x, y}] = cnt++;
        }
        unsigned long long r = a[{x, y}];
        ans += z*4;
        unsigned long long nx, ny;
        ny = y;
        nx = x+1;
        ans -= lose(num[r], num[a[{nx, ny}]], z);
        nx = x-1;
        ans -= lose(num[r], num[a[{nx, ny}]], z);
        nx = x;
        ny = y+1;
        ans -= lose(num[r], num[a[{nx, ny}]], z);
        ny = y-1;
        ans -= lose(num[r], num[a[{nx, ny}]], z);
        num[r] += z;
        printf("%llu\n", ans);
    }
}