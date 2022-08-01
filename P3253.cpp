//
// Created by kibi on 2021/8/26.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
    ll s,i;
};
ll n1,n2,sn,p,s;
ll ra[100005],tr[400005];
node ta[100005];
bool cmp(node a, node b){
    return a.s > b.s;
}
ll lowbit(ll x){
    return x&-x;
}
void add(ll x, ll s){
    for(ll i = x; i <= sn+1; i+=lowbit(i)){
        tr[i]+=s;
    }
}
// int ch(int x){
//     for(int i = x; i <= sa; i+=lowbit(i)){
//         tr[i]--;
//     }
// }
ll query(ll x){
    ll s = 0;
    for(ll i = x; i >= 1; i-=lowbit(i))s+=tr[i];
    return s;
}
int main(){
    cin >> n1 >> n2;
    sn = n1+n2;
    for(ll i = n1; i >= 1; i--){
        scanf("%lld", &ra[i]);
        ta[i].s = ra[i];
        ta[i].i = i;
        add(i, 1);
    }
    for(ll i = n1+2; i <= sn+1; i++){
        scanf("%lld", &ra[i]);
        ta[i].s = ra[i];
        ta[i].i = i;
        add(i, 1);
    }
    sort(ta+1, ta+2+sn, cmp);
    ll last = n1+1;
    for(ll i = 1; i <= sn; i++){
        s += fabs(query(last)-query(ta[i].i))-(ta[i].i>last);
        last = ta[i].i;
        add(ta[i].i, -1);
    }
    printf("%lld", s);
}