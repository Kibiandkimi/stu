//
// Created by kibi on 2021/8/31.
//
#include <bits/stdc++.h>
using namespace std;
int d[105][3005],t;
char a[105];
int main(){
    for(int i = 0; i <= 25; i++){
        d[1][i] = 1;
    }
    for(int i = 2; i <= 100; i++){
        int s = i*25;
        for(int j = 0; j <= s; j++){
            for(int k = j-25; k <= j; k++){
                if(k >= 0){
                    d[i][j] = (d[i][j] + d[i-1][k])%1000000007;
                }
            }
        }
    }
    cin >> t;
    while(t--){
        scanf("%s", a);
        int s = 0, num = 0;
        while(a[num]!=0){
            s += a[num]-'a';
            num++;
        }
        printf("%d\n", d[num][s]-1);
    }
    return 0;
}