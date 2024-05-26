//
// Created by kibi on 22-9-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[105], m, b[105], d[105][105];

void read(int &x);
void pre();
int judge(int a, int b = -1);
//int specialJudge(int a);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        a[i] = getchar();
    }
    read(m);
    for(int i = 1; i <= m; i++){
        b[i] = getchar();
    }
    pre();
    memset(d, 0xc0, sizeof d);
    d[0][0] = 0;
    for(int j = 1; j <= m; j++){
        //        d[0][j] = d[0][j-1] + b[j]=='A'?-3:b[j]=='C'?-4:b[j]=='G'?-2:-1;
        d[0][j] = d[0][j-1] + judge(b[j]);
    }
    for(int i = 1; i <= n; i++){
        //        d[i][0] = d[i-1][0] + a[i]=='A'?-3:a[i]=='C'?-4:a[i]=='G'?-2:-1;
        d[i][0] = d[i-1][0] + judge(a[i]);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            d[i][j] = max(d[i][j], max(d[i-1][j-1] + judge(a[i], b[j]), max(d[i-1][j] + judge(a[i]), d[i][j-1] + judge(b[j]))));
        }
    }
    printf("%d", d[n][m]);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if( c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void pre(){

}

int judge(int a, int b){
    if(b == -1){
        return a=='A'?-3:a=='C'?-4:a=='G'?-2:-1;
    }
    static int e[4][4] = {
            {5, -1, -2, -1},
            {-1, 5, -3, -2},
            {-2, -3, 5, -2},
            {-1, -2, -2, 5}
    };
    a = a=='A'?0:a=='C'?1:a=='G'?2:3;
    b = b=='A'?0:b=='C'?1:b=='G'?2:3;
    return e[a][b];
}