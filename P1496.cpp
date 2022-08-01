//
// Created by kibi on 2021/8/13.
//
#include <bits/stdc++.h>
using namespace std;
long long n,t,s;
struct node{
    long long x,e;
};
node a[20005];
bool cmp(node a, node b){
    return a.x<b.x;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        long long x1,x2,y1,y2;
        scanf("%lld %lld", &x1, &x2);
        a[i*2-1].x = x1;a[i*2-1].e = 1;
        a[i*2].x = x2;a[i*2].e = -1;
    }
    sort(a+1, a+1+n*2, cmp);
    for(int i = 1; i <= 2*n; i++){
        if(a[i].e==1){
            t++;
            s+=(a[i+1].x-a[i].x);
        }else{
            t--;
            if(t){
                s+=(a[i+1].x-a[i].x);
            }
        }
    }
    cout << s;
}