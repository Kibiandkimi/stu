//
// Created by kibi on 2021/7/31.
//
#include <bits/stdc++.h>
using namespace std;
int k,x,y;
int f(int a, int b, int x, int y, int s){
    if(s==0){
        return 0;
    }
    if(x <= a && y <= b){
        printf("%d %d 1\n", a+1, b+1);
        f(a-s/2,b+s/2,a,b+1,s/2);
        f(a+s/2,b+s/2,a+1,b+1,s/2);
        f(a+s/2,b-s/2,a+1,b,s/2);
        f(a-s/2,b-s/2,x,y,s/2);
    }else if(x <= a && y > b){
        printf("%d %d 2\n", a+1, b);
        f(a-s/2,b-s/2,a,b,s/2);
        f(a+s/2,b-s/2,a+1,b,s/2);
        f(a+s/2,b+s/2,a+1,b+1,s/2);
        f(a-s/2,b+s/2,x,y,s/2);
    }else if(x > a && y > b){
        printf("%d %d 4\n", a, b);
        f(a-s/2,b-s/2,a,b,s/2);
        f(a-s/2,b+s/2,a,b+1,s/2);
        f(a+s/2,b-s/2,a+1,b,s/2);
        f(a+s/2,b+s/2,x,y,s/2);
    }else if(x > a && y <= b){
        printf("%d %d 3\n", a, b+1);
        f(a-s/2,b-s/2,a,b,s/2);
        f(a-s/2,b+s/2,a,b+1,s/2);
        f(a+s/2,b+s/2,a+1,b+1,s/2);
        f(a+s/2,b-s/2,x,y,s/2);
    }
    return 0;
}
int main(){
    cin >> k >> x >> y;
    k = pow(2,k);
    f(k/2,k/2,x,y,k/2);
    return 0;
}