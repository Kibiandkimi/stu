//
// Created by kibi on 2022/4/10.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int ans[6][6] = {0,0,0,0,0,0,
                 0,1,1,1,1,1,
                 0,0,1,1,1,1,
                 0,0,0,2,1,1,
                 0,0,0,0,0,1,
                 0,0,0,0,0,0};
int nxtx[8] = {1,1,2,2,-2,-2,-1,-1};
int nxty[8] = {2,-2,1,-1,1,-1,2,-2};
int a[10][10], k;
int judge;

int check(){
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 5; j++){
            if(ans[i][j] != a[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

int test(int step){
    int cnt = 0;
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 5; j++){
            if(ans[i][j]!=a[i][j]){
                if(++cnt+step>k){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void f(int step, int x, int y, int pre){
    if(step==k){
        if(check()){
            judge = 1;
            return;
        }
    }
    if(judge){
        return;
    }
    for(int i = 0; i < 8; i++){
        int nx = x + nxtx[i], ny = y + nxty[i];
        if(nx<1||nx>5||ny<1||ny>5||i+pre==7){
            continue;
        }
        swap(a[x][y], a[nx][ny]);
        if(test(step)&&!judge){
            f(step+1, nx, ny, i);
        }
        swap(a[x][y], a[nx][ny]);
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        int x,y;
        judge = 0;
        for(int i = 1; i <= 5; i++){
            char ss[7];
            scanf("%s", &ss);
            for(int j = 0; j < 5; j++){
                if(ss[j]=='*'){
                    a[i][j+1] = 2;
                    x = i;
                    y = j+1;
                }else{
                    a[i][j+1] = ss[j] - '0';
                }
            }
        }
        for(k = 1; k <= 15; k++){
            f(0, x, y, -1);
            if(judge){
                printf("%d\n", k);
                break;
            }
        }
        if(!judge){
            printf("-1\n");
        }
    }
}