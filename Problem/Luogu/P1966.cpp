//
// Created by kibi on 2021/8/23.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,s;
ll ra[100005],rb[100005],a[100005],b[100005],t[100005];
map<ll, ll> m1,m2;
int f1(ll l, ll r){
    if(l==r){
        return 0;
    }
    ll mid = (l+r)/2;
    f1(l,mid);f1(mid+1,r);
    //    int t[100005];
    ll t1 = l, t2 = mid+1,i=0;
    while(t1<=mid&&t2<=r){
        if(m2[ra[t1]]<m2[ra[t2]]){
            t[i++] = ra[t1++];
        }else{
            t[i++] = ra[t2++];
            s += mid-t1+1;
        }
    }
    while(t2<=r){
        t[i++] = ra[t2++];
    }
    while(t1<=mid){
        t[i++] = ra[t1++];
    }
    for(ll j = l; j <= r; j++){
        ra[j] = t[j-l];
    }
    return 0;
}
int main(){

    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        ra[i] = a[i];
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        rb[i] = b[i];
        m1[b[i]] = i;
    }
    sort(b+1, b+1+n);
    sort(a+1,a+1+n);
    for(int i = 1; i <= n; i++){
        m2[a[i]] = m1[b[i]];
    }
    f1(1,n);
    cout << s%(100000000-3);
}