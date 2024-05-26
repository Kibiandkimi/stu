//
// Created by kibi on 22-9-4.
//
//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
long long n, rx, rp, rq, t[100005], x, p, q, ans, avl;

bool getType(long long c);
void read(long long &x);

int main(){
    //    freopen("t.in", "r", stdin);
    read(n), read(rx), read(rp), read(rq);
    x = rx*rq, q = rq * x, p = rp * rx, avl = x-p;
    for(int i = 1; i <= n; i++){
        read(t[i]);
        t[i] *= rq;
    }
    long long now = 0, i = 1;
    ans = 0;
    while(i<=n) {
        long long sum = 0;
        //        ans++, now += avl;
        while (i <= n && now - t[i] >= 0 && sum+t[i] < x) {
            now = now - t[i];
            sum += t[i];
            i++;
        }
        if(i <= n){
            long long del = ceil(((double)t[i]-(double)now)/(double)avl);
            if(del <= 0){
                del = 1;
            }
            ans += del;
            now += del*avl;
        }
    }
    printf("%lld", ans);
    //    fclose(stdin);
}

bool getType(long long c){
    return c < '0' || '9' < c;
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}