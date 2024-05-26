//
// Created by kibi on 2022/9/24.
//
#include <bits/stdc++.h>
using namespace std;
int T, n, a[15];
bool f1, f2, f3, d[105];

void read(int &x);

int main(){
    read(T);
    while(T--){
        int x;
        f1 = f2 = f3 = false;
        read(n), read(x);
        for(int i = 1; i <= n; i++){
            read(a[i]);
            if(a[i] > 0){
                f1 = true;
            }else if(a[i] < 0){
                f2 = true;
            }else{
                f3 = true;
            }
            a[i] = a[i]<0?-a[i]:a[i];
        }
        if((f1 && x > 0) || (f2 && x < 0) || f3){
            printf("Yes\n");
            continue;
        }
        x = x<0?-x:x;
        memset(d, 0, sizeof d);
        d[x] = true;
        bool flag = false;
        for(int i = x; i > 0; i--){
            if(d[i]){
                for(int j = 1; j <= n; j++){
                    if(i-a[j]<0){
                        flag = true;
                        break;
                    }else{
                        if(a[j] < 0 || x < 0){
                            throw "error";
                        }
                        d[i-a[j]] = true;
                    }
                }
                if(flag){
                    break;
                }
            }
        }
        if(flag){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
}

void read(int &x){
    //    scanf("%d", &x);
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}