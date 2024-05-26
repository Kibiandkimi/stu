//
// Created by kibi on 2021/7/22.
//
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[1000005], s[2][1000005], b[1000005];
queue<long long> q;
int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    long long mmin = 1e15, mmax = -1e15;
    for(int i = 1; i <= k; i++){
        q.push(a[i]);
        mmin = min(mmin, a[i]);
        mmax = max(mmax, a[i]);
    }
    s[0][1] = mmin;
    s[1][1] = mmax;
    for(int i = k+1; i <= n; i++){
        int x = i - k + 1, y = i;
        int t = q.front();
        q.pop();
        q.push(a[i]);
        if(t==mmin||t==mmax){
            mmin = 1e15;
            mmax = -1e15;
            for(int j = x; j <= y; j++){
                mmin = min(a[j], mmin);
                mmax = max(a[j], mmax);
            }
        }else{
            mmin = min(a[i], mmin);
            mmax = max(a[i], mmax);
        }
        s[0][x] = mmin;
        s[1][x] = mmax;
    }
    for(int i = 1; i <= n-k+1; i++){
        cout << s[0][i] << " ";
    }
    cout << endl;
    for(int i = 1; i <= n-k+1; i++){
        cout << s[1][i] << " ";
    }
    //    for(int i = 1; i <= k; i++){
    //        b[i]=a[i];
    //        mmin = min(a[i], mmin);
    //        mmax = max(a[i], mmax);
    //    }
    //    s[0][1]=mmin;
    //    s[1][1]=mmax;
    //    sort(b+1, b+1+k);
    //    for(int i = k; i <= n; i++){
    //        int x = i-k+1, y = i;
    //
    //    }
}