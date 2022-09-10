#include <bits/stdc++.h>
using namespace std;
int n, a[100005];
int l, r;

void read(int &x);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        if(!l && a[i]!=3){
            l = i;
        }
        if(a[i]!=2){
            r = i;
        }
    }
    int ans = 0;
    for(int i = l; i <= r; i++){

    }

}