//
// Created by kibi on 2022/9/23.
//
#include <bits/stdc++.h>
using namespace std;
int T, n, k;
long long a[200005];

void read(int &x);

int main(){
    read(T);
    while(T--){
        read(n), read(k);
        int p = 1;
        a[0] = 0;
        int tem1;
        read(tem1);
        a[1] = tem1;
        for(int i = 2; i <= n; i++){
            int t;
            read(t);
            if((t > 0 && a[p] < 0) || (t < 0 && a[p] > 0) || t == 0 || a[p] == 0){
                a[++p] = t;
            }else{
                a[p] += t;
            }
            if(i == k){
                k = p;
            }
        }
        n = p;
        a[p+1] = 0;
        bool flag = true;
        int l = k-1, r = k+1;
        long long now = a[k], ls = 0, rs = 0;
        while (l != 0 && r != p + 1) {
            bool fl = false, fr = false;
            if(now+a[l]+ls>=0){
                ls += a[l];
                if(ls > 0){
                    now += ls, ls = 0;
                }
                l--;
                fl = true;
            }
            if(now+a[r]+rs>=0){
                rs += a[r];
                if(rs > 0){
                    now += rs, rs = 0;
                }
                r++;
                fr = true;
            }
            if(!(fl || fr)){
                flag = false;
                break;
            }
        }
        if(flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
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