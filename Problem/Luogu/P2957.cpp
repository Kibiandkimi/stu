//
// Created by kibi on 2022/4/7.
//
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
string a,b;
int la,lb,l;
int ans;
ull p[105], hl[105], hr[105];
ull get(ull h[], int l, int r){
    return h[r] - h[(l-1)==-1?104:(l-1)]*p[r-l];
}
int main(){
    hl[104] = 1;
    hr[104] = 1;
    cin >> a >> b;
    la = a.length();
    lb = b.length();
    l = max(la, lb);
    p[0] = 131;
    hl[0] = 131+(a[0]-96);
    hr[0] = 131+(b[0]-96);
    for(int i = 1; i < la; i++){
        hl[i] = hl[i-1]*131+(a[i]-96);
    }
    for(int i = 1; i < lb; i++){
        hr[i] = hr[i-1]*131+(b[i]-96);
    }
    for(int i = 1; i < l; i++){
        p[i] = p[i-1]*131;
    }

    for(int i = 1; i <= l; i++){
        int al, bl;
        if(la<i || lb<i){
            break;
        }
        al = get(hl, 0, i-1)!=get(hr, lb-i, lb-1)?-100000000:i;
        bl = get(hr, 0, i-1)!=get(hl, la-i, la-1)?-100000000:i;
        ans = max(ans, max(al, bl));
    }
    printf("%d", ans);
    return 0;
}