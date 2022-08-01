//
// Created by kibi on 2021/9/12.
//
#include <bits/stdc++.h>
using namespace std;
long long n,s;
struct node{
    int s,next;
}a[1000005];
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i].s);
        a[i].next = i+1;
    }
    bool f = true;
    while(f){
        f = false;
        for(int i = 1; a[a[i].next].next <= n&&a[a[i].next].next; i=a[i].next){
            if((a[i].s&a[a[a[i].next].next].s)>(a[a[i].next].s&a[i].s)+(a[a[i].next].s&a[a[a[i].next].next].s)){
                a[i].next = a[a[i].next].next;
                f = true;
            }
        }
    }
    for(int i = 1; a[i].next <= n; i=a[i].next){
        s += a[i].s&a[a[i].next].s;
    }
    printf("%lld", s);
}