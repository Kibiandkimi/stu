//
// Created by kibi on 22-8-24.
//
#include <bits/stdc++.h>
using namespace std;
int a, b, p;
int c[100005];
//vector<int> z;

int find(int x){
    if(x != c[x]){
        return c[x] = find(c[x]);
    }
    return x;
}

int main(){
    scanf("%d %d %d", &a, &b, &p);
    for(int i = a; i <= b; i++){
        c[i] = i;
    }
    int s = b-a+1;
    for(int i = max(p, 2); i <= b; i++){
        bool flag = true;
        for(int j = 2; j * j <= i; j++){
            if(i%j==0){
                flag = false;
                j = i;
            }
        }
        if(flag){
            int r = 0;
            for(int j = i; j <= b; j+=i){
                if(r){
                    if(find(c[j]) != find(r)) {
                        s--;
                        c[find(c[j])] = find(r);
                    }
                }else if(c[j]){
                    r = c[j];
                }
            }
        }
    }

    printf("%d", s);
}