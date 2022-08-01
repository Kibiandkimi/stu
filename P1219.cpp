//
// Created by kibi on 2021/7/9.
//
#include<bits/stdc++.h>
using namespace std;
int y[15],sum,l[15];
int lt[35],rt[35];
int m;
int f(int n){
    if(n==0){
        sum++;
        if(sum<=3){
            for(int i = 0; i < m; i++){
                cout << l[i] << " ";
            }
            cout << endl;
        }
        return 0;
    }
    for(int i = 1; i <= m; i++){
        if(y[i]==0&&lt[i-n+m]==0&&rt[i+n]==0){
            y[i]=1;
            lt[i-n+m]=1;
            rt[i+n]=1;
            l[m-n]=i;
            f(n-1);
            l[m-n]=0;
            y[i]=0;
            lt[i-n+m]=0;
            rt[i+n]=0;
        }
    }
    return 0;
}
int main(){
    cin >> m;
    f(m);
    cout << sum;
}