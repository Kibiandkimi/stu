//
// Created by kibi on 22-8-16.
//
//100pts在上，神奇的40pts在下
#include <bits/stdc++.h>
using namespace std;
int n, a[105], d1[105], d2[105];
//int tr[405], lit[105];

//void insert(int x){
//    for(;x<=n;x+=(x&-x)){
//        tr[x]++;
//    }
//}
//
//int query(int x){
//    int res = 0;
//    for(;x>=1;x-=(x&-x)){
//        res += tr[x];
//    }
//    return res;
//}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        d1[i] = 1;
        d2[i] = 1;
//        lit[i] = query(a[i]);
//        insert(a[i]);
    }
//    int ans = n-1;
//    d1[1] = 0;
//    int nd = a[1], ndd = 0;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++){
            if(a[i] > a[j] && d1[i]<=d1[j]+1){
                d1[i] = d1[j]+1;
            }
        }
    }
//    d2[n] = 0;
//    nd = a[n], ndd = 0;
    for(int i = n-1; i >= 1; i--){
        for(int j = i+1; j <= n; j++){
            if(a[i] > a[j] && d2[i]<=d2[j]+1){
                d2[i] = d2[j]+1;
            }
        }
    }
    int ans = 1;
    for(int i = 0; i <= n; i++){
        ans = max(ans, d1[i]+d2[i]-1);
    }
    printf("%d", n-ans);
}
/*
#include <bits/stdc++.h>
using namespace std;
int n, a[105], d1[105], d2[105];
//int tr[405], lit[105];

//void insert(int x){
//    for(;x<=n;x+=(x&-x)){
//        tr[x]++;
//    }
//}
//
//int query(int x){
//    int res = 0;
//    for(;x>=1;x-=(x&-x)){
//        res += tr[x];
//    }
//    return res;
//}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
//        lit[i] = query(a[i]);
//        insert(a[i]);
    }
//    int ans = n-1;
    d1[1] = 0;
    int nd = a[1], ndd = 0;
    for(int i = 2; i <= n; i++){
        if(a[i]>nd){
            d1[i] = d1[i-1];
            ndd = nd;
            nd = a[i];
        }else if(a[i] > ndd){
            nd = a[i];
            d1[i] = d1[i-1]+1;
        }else{
            d1[i] = d1[i-1]+1;
        }
    }
    d2[n] = 0;
    nd = a[n], ndd = 0;
    for(int i = n-1; i >= 1; i--){
        if(a[i] > nd){
            d2[i] = d2[i+1];
            ndd = nd;
            nd = a[i];
        }else if(a[i] > ndd){
            nd = a[i];
            d2[i] = d2[i+1]+1;
        }else{
            d2[i] = d2[i+1]+1;
        }
    }
    int ans = n-1;
    for(int i = 0; i <= n; i++){
        ans = min(ans, d1[i]+d2[i+1]);
    }
    printf("%d", ans);
}*/


// 2023/7/20

/*
 * #include <bits/stdc++.h>
using namespace std;

const int N = 100;

void read(int&);

int main(){
    int n;
    read(n);
    int a[N + 5], f1[N + 5] = {0}, f2[N + 5] = {0};
    for(int i = 1; i <= n; i++){
        read(a[i]);

    }
    int ans = n;
    for(int i = 1; i <= n; i++){
        f1[i] = 1;
        f2[n-i+1] = 1;
        for(int j = i-1; j >= 1; j--){
            if(a[j]<a[i]){
                f1[i] = max(f1[i], f1[j]+1);
            }
            if(a[n-j+1] < a[n-i+1]){
                f2[n-i+1] = max(f2[n-i+1], f2[n-j+1]+1);
            }
        }

    }

    for(int i = 1; i <= n; i++){
        ans = n-max(n-ans, f1[i]+f2[i]-1);
    }

    printf("%d\n", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c= getchar();
    }
    x = s * w;
}
 * */