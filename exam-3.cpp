//
// Created by kibi on 2021/6/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
int f(int n,int m){
    if(n == 0){
        cout << 2*(m+1);
        return 0;
    }
    printf("After hour #%d left %d.\n",n,2*(m+1));
    f(n-1,2*(m+1));
}
int main(){
    cin >> n >> m;
    printf("After hour #%d left %d.\n",n-1,m);
    f(n-2,m);
}