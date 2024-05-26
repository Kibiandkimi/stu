//
// Created by kibi on 22-8-28.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, y[200005], k_s[2005], sk;
bool a[200005], k_a[2005];

bool getBoolean(int c) { return c < '0' || '9' < c; }

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getBoolean(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getBoolean(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

int query(int l, int r){
    if(y[r]-y[l]<=1){
        int ans = 0;
        for(int i = l; i <= r; i++){
            ans += a[i]^k_a[y[i]];
        }
        return ans;
    }else{
        int ans = a[l]^k_a[y[l]];
        for(int i = l+1; (i-1) % sk; i++){
            ans += a[i]^k_a[y[i]];
        }
        for(int i = ((r-1)/sk)*sk+1; i <= r; i++){
            ans += a[i]^k_a[y[i]];
        }
        for(int i = y[l]+1; i < y[r]; i++){
            ans += k_s[i];
        }
        return ans;
    }
}

void change(int l, int r){
    if(y[r]-y[l]<=1){
        for(int i = l; i <= r; i++){
            if(a[i]){
                a[i] = false;
                k_s[y[i]] += k_a[y[i]]?1:-1;
            }else{
                a[i] = true;
                k_s[y[i]] += k_a[y[i]]?-1:1;
            }
        }
        return ;
    }else{
        if(a[l]){
            a[l] = false;
            k_s[y[l]] += k_a[y[l]]?1:-1;
        }else{
            a[l] = true;
            k_s[y[l]] += k_a[y[l]]?-1:1;
        }
        for(int i = l+1; (i-1) % sk; i++){
            if(a[i]){
                a[i] = false;
                k_s[y[i]] += k_a[y[i]]?1:-1;
            }else{
                a[i] = true;
                k_s[y[i]] += k_a[y[i]]?-1:1;
            }
        }
        for(int i = ((r-1)/sk)*sk+1; i <= r; i++){
            if(a[i]){
                a[i] = false;
                k_s[y[i]] += k_a[y[i]]?1:-1;
            }else{
                a[i] = true;
                k_s[y[i]] += k_a[y[i]]?-1:1;
            }
        }
        for(int i = y[l]+1; i < y[r]; i++){
            k_a[i] = !k_a[i];
            if(y[n] != i){
                k_s[i] = sk - k_s[i];
            }else{
                k_s[i] = n%sk - k_s[i];
            }
        }
    }
}

int main(){
    read(n);
    read(m);
    sk = sqrt(n);
    for(int i = 1; i <= n; i++){
        y[i] = (i-1)/sk+1;
    }
    while(m--){
        int c, l, r;
        read(c), read(l), read(r);
        if(c==1){
            int ans = query(l, r);
            printf("%d\n", ans);
        }else{
            change(l, r);
        }
    }
}