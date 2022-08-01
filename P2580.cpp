//
// Created by kibi on 2021/10/7.
//
#include <bits/stdc++.h>
using namespace std;
string ernm, t;
int n,m;
// int cnt = 1;
// vector<node> tr[2005];
// int ls[55][30];
map<string, int> a;
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        cin >> t;
        a[t]++;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        cin >> t;
        if(a[t]==0){
            printf("WRONG\n");
        }else if(a[t]==1){
            printf("OK\n");
            a[t]++;
        }else{
            printf("REPEAT\n");
        }
    }
}