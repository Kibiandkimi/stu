//
// Created by kibi on 2021/10/1.
//
#include <bits/stdc++.h>
using namespace std;
long long n,q,a[1000005],k,f[1000005],v[1000005],head,tail;
int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
    scanf("%lld", &q);
    while(q--){
        scanf("%lld", &k);
        head = tail = 1;
        v[head] = 1;
        for(int i = 2; i <= n; i++){
            while(head<=tail&&i-v[head]>k){
                head++;
            }
            if(a[v[head]]>a[i])f[i] = f[v[head]];
            else f[i] = f[v[head]]+1;
            while(f[v[tail]]>f[i]||f[v[tail]]==f[i]&&a[v[tail]]<=a[i])tail--;
            tail++;
            v[tail] = i;
        }
        printf("%lld\n", f[n]);
    }
}