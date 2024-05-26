//
// Created by kibi on 2021/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,p,a[5000005],s[5000005];
int main(){
    cin >> n >> p;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++){
        s[i] = a[i]-a[i-1];
    }
    for(int i = 1; i <= p; i++){
        int t1,t2,t3;
        cin >> t1 >> t2 >> t3;
        s[t1]+=t3;
        s[t2+1]-=t3;
    }
    int mmin = 1e9;
    for(int i = 1; i <= n; i++){
        a[i]=a[i-1]+s[i];
        mmin=min(mmin,a[i]);
    }
    cout << mmin;
}