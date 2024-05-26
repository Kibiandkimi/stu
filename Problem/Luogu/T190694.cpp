//
// Created by kibi on 2021/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int a[65][65],vis[65],s,ls;
bool ff;
int f(int x){
    for(int i = 1; i <= n; i++){
        if(a[x][i]&&vis[i]!=x){
            if(vis[i] != ls){
                ff = true;
                ls = vis[i];
            }
            vis[i]=x;
            f(i);
        }
    }
    return 0;
}
bool pd(int x){
    for(int i = 1; i <= n; i++){
        if(vis[i]!=x){
            return true;
        }
    }
    return false;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        string t;
        cin >> t;
        for(int j = 0; j < n; j++){
            a[i][j+1] = t[j] == '1';
        }
    }
    for(int i = 1; i <= n; i++){
        ff = false;
        f(i);
        if(ff||pd(i)){
            s++;
        }
    }
    cout << s;
}