//
// Created by kibi on 2021/7/5.
//
#include<bits/stdc++.h>
using namespace std;
int n,k,a[25],s;
int f(int nn, int ii){
    if(nn==0){
        for(int i = 2; i*i<=s; i++){
            if(s%i==0){
                return 0;
            }
        }
        return 1;
    }
    int sum = 0;
    for(ii+=1;ii<n;ii++){
        s+=a[ii];
        sum+=f(nn-1,ii);
        s-=a[ii];
    }
    return sum;
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++)cin>>a[i];
    cout << f(k,-1);
}