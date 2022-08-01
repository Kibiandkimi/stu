//
// Created by kibi on 2021/7/25.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int a[505],b[505];
int main(){
    cin >> n;
    int p = n;
    int ss = log10(2)*n+1;
    a[1] = 2;
    b[1] = 1;
    while(p!=0){
        int ta[1050],tb[1050];
        for(int i = 1; i <= 502; i++){
            ta[i] = a[i];
            tb[i] = b[i];
            a[i]=0;
            if(p%2==1) {
                b[i] = 0;
            }
        }
        if(p%2==1){
            for(int i = 1; i <= 502; i++){
                for(int j = 1; j <= 502; j++){
                    b[j-1+i]+=ta[i]*tb[j];
                    b[j+i]+=b[j-1+i]/10;
                    b[j-1+i]%=10;
                }
            }
            p--;
        }
        if(p==0)break;
        for(int i = 1; i <= 502; i++){
            for(int j = 1; j <= 502; j++){
                a[j-1+i]+=ta[i]*ta[j];
                a[j+i]+=a[j-1+i]/10;
                a[j-1+i]%=10;
            }
        }
        p/=2;
    }
    b[1]-=1;
    cout << ss;
    for(int i = 500; i >= 1; i--){
        if(i%50==0){
            cout << endl;
        }
        cout << b[i];

    }
}