//
// Created by kibi on 2022/9/2.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);
void read(unsigned long long &x);
void jx(unsigned long long x, bool *f);

int main(){
    static int n, m, c, k, cnt = 0, s[1000005] = {0};
    bool f[70] = {false};
    vector<int> b[70];
    read(n), read(m), read(c), read(k);
    for(int i = 1; i <= n; i++){
        unsigned long long x;
        read(x);
        jx(x, f);
    }
    for(int i = 1; i <= m; i++){
        int p, q;
        read(p), read(q);
        if(f[p]) {
            s[cnt++] = q;
        }else{
            b[p].push_back(q);
        }
    }
    sort(s, s+cnt);
    //    int k = 64;
    for(int i = 0; i < k; i++){
        if(!f[i]){
            int sb = b[i].size();
            bool flag = true;
            for(int j = 0; j < sb; j++){
                int l = 0, r = cnt-1, t = b[i][j];
                while(l<r){
                    int mid = (l+r)/2;
                    if(s[mid]<t){
                        l = mid+1;
                    }else{
                        r = mid;
                    }
                }
                if(s[l] != t){
                    flag = false;
                    j = sb;
                }
            }
            f[i] = flag;
        }
    }
    int sum = 0;
    for(int i = 0; i < k; i++){
        sum += f[i];
    }
    unsigned long long ans = 0;
    if(sum == 0){
        printf("0");
    }else{
        ans = 2;
        for(int i = 2; i <= sum; i++){
            ans = ans*2;
        }
        ans = ans - (unsigned long long)n;
        //        坑点在这
        if(ans==0&&n==0){
            printf("18446744073709551616");
            return 0;
        }
        //
        printf("%llu", ans);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void read(unsigned long long &x){
    unsigned long long s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        unsigned long long t = c-'0';
        s = s*10 + t;
        c = getchar();
    }
    x = s*w;
}

void jx(unsigned long long x, bool *f){
    int i = 0;
    while(x){
        f[i++] |= x%2;
        x/=2;
    }
}