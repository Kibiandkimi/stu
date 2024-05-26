//
// Created by kibi on 2021/6/20.
//
#include <bits/stdc++.h>
using namespace std;
int a [1005][1005];
int main(){
    int n , m;
    cin >> n >> m ;
    for ( int i = 1 ; i <= m ; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[x1][y1] += 1;
        a[x1][y2+1] += -1;
        a[x2+1][y1] += -1;
        a[x2+1][y2+1] += 1;
    }
    for(int j = 1 ; j <= n ; j++ ) {
        for ( int i = 1 ; i <= n ; i++ ) {
            a[i][j] += a[i-1][j] ;
        }
    }


    for ( int i = 1 ; i <= n ; i++){
        for ( int j = 1 ; j <= n ; j++ ) {
            a[i][j]+=a[i][j-1];
        }
    }
    int ans = 0;
    for ( int i = 1 ; i <= n ; i++ ) {
        for ( int j = 1 ; j <= n ; j++ ) {
            ans = ans ^ a[i][j];

        }
    }
    cout << ans << endl;
}