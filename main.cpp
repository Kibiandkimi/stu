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
    int ans = 2;
    for(int i = l+1; i < r; i++){
        ans += a[i]==1;
    }
    printf("%d", l==r||l!=0?1:ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}