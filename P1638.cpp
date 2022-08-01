//
// Created by kibi on 2021/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1000005],vis[1000005];
bool chk(){
    for(int i = 1; i <= m; i++){
        if(!vis[i])return false;
    }
    return true;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int x,y;
    x = 1;
    y = 1;
    vis[a[1]]++;
    int mmin, mx, my, ls;
    while(!chk()){
        y++;
        vis[a[y]]++;
    }
    vis[a[x]]--;
    ls = a[x];
    mmin=y-x;
    mx=x;
    my=y;
    for(x = 2; x <= n; x++){
        while(!vis[ls]){
            y++;
            vis[a[y]]++;
            if(y>n)break;
        }
        if(y>n)break;
        vis[a[x]]--;
        ls = a[x];
        if(y-x<mmin){
            mmin=y-x;
            mx=x;
            my=y;
        }
    }
    cout << mx << " " << my;
}