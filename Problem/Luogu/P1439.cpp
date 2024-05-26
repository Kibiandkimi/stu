//
// Created by kibi on 22-8-15.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[100005], b[100005], ma[100005], d[100005];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        ma[a[i]] = i;
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        d[i] = 1e9;
    }
    int len = 0;
    d[0] = 0;
    for(int i = 1; i <= n; i++){
        int l = 0, r = len, mid;
        if(ma[b[i]] > d[len]){
            d[++len] = ma[b[i]];
        }else{
            while (l < r){
                mid = (l + r)/2;
                if(d[mid]>ma[b[i]]){
                    r = mid;
                }else{
                    l = mid+1;
                }
            }
            d[l] = min(ma[b[i]], d[l]);
        }
    }
    printf("%d", len);
}