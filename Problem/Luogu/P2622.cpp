//
// Created by kibi on 2022/9/29.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int d[1505], opt[105][15];
bool flag;

void read(int &x);

int main(){
    memset(d, 0x3f, sizeof d);
    read(n), read(m);
    if(n == 0){
        printf("0");
        return 0;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            read(opt[i][j]);
        }
    }
    queue<int> q;
    q.push((1<<n)-1);
    d[(1<<n)-1] = 0;
    //    vis[(1<<n)-1] = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 1; i <= m; i++){
            int t = u;
            for(int j = 1; j <= n; j++){
                t = opt[i][j]==-1?(t|(1<<(j-1))):opt[i][j]==1?((t|(1<<(j-1)))==t?(t^(1<<(j-1))):t):t;
            }
            if(d[t]>d[u]+1){
                flag |= !(bool)t;
                d[t] = d[u]+1;
                q.push(t);
            }
        }
    }

    printf("%d\n", flag?d[0]:-1);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
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