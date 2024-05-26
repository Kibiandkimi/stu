//
// Created by kibi on 2021/8/15.
//
#include <bits/stdc++.h>
using namespace std;
int n,vis[10005];
vector<int> a;
vector<int> b;
int main(){
    cin >> n;
    for(int i = 2; i <= 10005; i++){
        bool flag = true;
        for(int j = 2; j * j <= i; j++){
            if(i%j==0){
                flag = false;
                j = i;
            }
        }
        if(flag){
            a.push_back(i);
        }
    }
    int mx = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; a[j]<i; j++){
            vis[b[i-a[j]-1]] = i;
        }
        int j;
        for(j = 1; vis[j]==i; j++){}
        b.push_back(j);
        mx = max(mx, j);
    }
    printf("%d\n", mx);
    int sb = b.size();
    for(int i = 0; i < sb; i++)printf("%d ", b[i]);
    return 0;
}