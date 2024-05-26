//
// Created by kibi on 2021/9/26.
//
#include <bits/stdc++.h>
using namespace std;
int d[5005][5005],v[5005][5005],n,q;
string a;
bool f(int l ,int r){
    if(r<l){
        return false;
    }
    if(v[l][r] == 0){
        v[l][r] = ((r-l<2)&&(a[l-1]==a[r-1])||f(l+1, r-1)&&(a[l-1]==a[r-1]))?1:-1;
    }
    if(v[l][r] == -1){
        return false;
    }else if(v[l][r] == 1){
        return true;
    }
    //    return false;
}
int main(){
    cin >> a >> q;
    n = a.size();

    for(int i = 1; i <= n; i++){
        int tl = n - i + 1;
        // cout << i << endl;
        for(int l = 1; l <= tl; l++){
            // cout << l << endl;
            int r = l+i-1;
            d[l][r] = d[l+1][r] + d[l][r-1] - d[l+1][r-1] + f(l,r);
            // cout << l << endl;
        }
    }
    for(int i = 1; i <= q; i++){
        int tl,tr;
        scanf("%d %d", &tl, &tr);
        printf("%d\n", d[tl][tr]);
    }
}