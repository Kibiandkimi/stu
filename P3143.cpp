//
// Created by kibi on 2021/8/10.
//
#include <bits/stdc++.h>
using namespace std;
long long n,k;
long long l,r,mxl;
long long a[50005],mx;
long long ll[50005], rr[50005];
int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    sort(a+1, a+1+n);
    l = 0;
    r = 1;
    mxl = 0;
    for(long long i = 1; i <= n; i++){
        while(r+i<=n&&a[i+r]-a[i]<=k)r++;
        while(a[i-1]-a[i-l]>k)l--;
        mxl = max(mxl, l);
        mx = max(mx, mxl+r);
        l++;
        r--;
        //        cout << l << " " << r << endl;
        //        cout << a[i] << endl;
    }
    cout << mx;
}