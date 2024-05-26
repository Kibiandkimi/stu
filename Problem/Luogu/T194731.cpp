//
// Created by kibi on 2021/8/15.
//

#include <bits/stdc++.h>
using namespace std;
int l,q;
char a[2005][2005];
char z;
int main(){
    cin >> l >> q;
    scanf("%c ", &z);
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= l; j++){
            scanf("%c ", &a[i][j]);
        }
    }
    for(int i = 1; i <= q; i++){
        int x,y,s=0;
        scanf("%d %d", &x, &y);
        int t = 1;
        while((x-t)>0&&(x+t)<=l&&a[x-t][y]==a[x+t][y]){
            t++;
        }
        s = max((t-1)*2+1, s);
        t = 1;
        while((y-t)>0&&(y+t)<=l&&a[x][y-t]==a[x][y+t]){
            t++;
        }
        s = max((t-1)*2+1, s);
        printf("%d\n", s);
    }
}