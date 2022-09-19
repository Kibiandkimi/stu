//
// Created by kibi on 22-9-19.
//
#include <bits/stdc++.h>
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
unsigned long long read(){
    register unsigned long long x=0,f=1;
    register int ch=getchar();
    for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
int main(){
    // scanf("%d", &n);
//    freopen("t.in", "r", stdin);
    register unsigned long long n;
    register unsigned long long a[35] = {0};
    register unsigned long long s[35] = {0};
    register unsigned long long ans = 0;
    n = read();
    for(register int i = 1; i <= n; i++) {
        // scanf("%llu", &a[i]);
        a[i] = read();
        s[i] = s[i-1]^a[i];
    }
    register unsigned long long k = (1<<n);
    register unsigned long long r = 0;
    //    int j = 0;
    //    for(register unsigned long long i = 1; i <= k; ++i){
    //        register unsigned long long tt = i&-i;
    //        while(tt){
    //            tt >>= 1;
    //            j++;
    //        }
    //        r ^= s[j];
    //        ans ^= r*i;
    //        j = 0;
    //    }
    for (register int i=1;i<k;i++)
    {
        register int j = __builtin_ffs(i);
        //        for (register int j=__builtin_ffs(i);j;j--)
        //            r^=a[j];
        r ^= s[j];
        ans^=r*i;
    }
    printf("%llu", ans);
//    fclose(stdin);
}