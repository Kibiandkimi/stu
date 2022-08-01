//
// Created by kibi on 2021/10/10.
//
#include <bits/stdc++.h>
using namespace std;
long long n, h, s;
// stack<long long> a;
struct node{
    long long x,s;
};
stack<node> a;
int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &h);
        int t = 1;
        while(a.size() && a.top().x <= h){
            if(a.top().x==h){
                t+=a.top().s;
            }
            s += a.top().s;
            a.pop();
            // s++;
        }
        if(a.size()){
            s++;
        }
        // while(t--){
        //     a.push(h);
        // }
        a.push(node({h,t}));
    }
    printf("%lld", s);
    return 0;
}