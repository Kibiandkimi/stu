//
// Created by kibi on 2022/8/29.
//
#include <bits/stdc++.h>
using namespace std;
long long n, f;

bool getBoolean(long long c) { return c < '0' || '9' < c; }
void read(long long &x){
    long long s = 0, w = 1, c = getchar();
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

struct Node{
    long long tag = 0, sum = 0;
    int l = 0, r = 0;
}node[2005];
/*, k_tag[2005], k_sum[2005], s_k, k_l[2005], k_r[2005]*/
long long a[200005];
int y[200005], s_k;
void update(int l, int r, long long k){
    if(l>r){
        throw "l>r error";
    }
    if(y[r]-y[l]<=1){
        for(int i = l; i <= r; i++){
            a[i] += k;
            node[y[i]].sum += k;
        }
    }else{
        for(int i = l; i <= node[y[l]].r; i++){
            a[i] += k;
            node[y[i]].sum += k;
        }
        for(int i = node[y[r]].l; i <= r; i++){
            a[i] += k;
            node[y[i]].sum += k;
        }
        for(int i = y[l]+1; i < y[r]; i++){
            node[i].tag += k;
            node[i].sum += k*(node[i].r-node[i].l+1);
        }
    }
}

long long query(int l, int r){
    if(l>r){
        throw "l>r error";
    }
    long long ans = 0;
    if(y[r]-y[l] <= 1){
        for(int i = l; i <= r; i++){
            ans += a[i]+node[y[i]].tag;
        }
        return ans;
    }else{
        for(int i = l; i <= node[y[l]].r; i++){
            ans += a[i]+node[y[l]].tag;
        }
        for(int i = node[y[r]].l; i <= r; i++){
            ans += a[i]+node[y[r]].tag;
        }
        for(int i = y[l]+1; i < y[r]; i++){
            ans += node[i].sum;
        }
        return ans;
    }
}

//#define read(a) scanf("%lld", &a)

int main(){
    read(n);
    read(f);
    s_k = sqrt(n);
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    for(int i = 1; i <= n; i++){
        y[i] = (i-1)/s_k+1;
        //      艹，/s_k 写成 %s_k了
        node[y[i]].sum += a[i];
        if(!node[y[i]].l){
            node[y[i]].l = i;
        }
        node[y[i]].r = i;
    }
    while(f--){
        long long op;
        read(op);
        if(op == 1){
            long long l, r, k;
            read(l), read(r), read(k);
            update((int)l, (int)r, k);
        }else if(op == 2){
            long long k;
            read(k);
            update(1, 1, k);
        }else if(op == 3){
            long long k;
            read(k);
            update(1, 1, -k);
        }else if(op == 4){
            long long l, r;
            read(l), read(r);
            long long ans = query((int)l, (int)r);
            printf("%lld\n", ans);
        }else if(op == 5){
            long long ans = query(1, 1);
            printf("%lld\n", ans);
        }else{
            throw "op<1 or op>5 error";
        }
    }
}