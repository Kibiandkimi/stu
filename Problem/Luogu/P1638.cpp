//
// Created by kibi on 2021/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1000005],vis[1000005];
bool chk(){
    for(int i = 1; i <= m; i++){
        if(!vis[i])return false;
    }
    return true;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int x,y;
    x = 1;
    y = 1;
    vis[a[1]]++;
    int mmin, mx, my, ls;
    while(!chk()){
        y++;
        vis[a[y]]++;
    }
    vis[a[x]]--;
    ls = a[x];
    mmin=y-x;
    mx=x;
    my=y;
    for(x = 2; x <= n; x++){
        while(!vis[ls]){
            y++;
            vis[a[y]]++;
            if(y>n)break;
        }
        if(y>n)break;
        vis[a[x]]--;
        ls = a[x];
        if(y-x<mmin){
            mmin=y-x;
            mx=x;
            my=y;
        }
    }
    cout << mx << " " << my;
}

// 2023/7/19

/*
#include <bits/stdc++.h>
using namespace std;

const int N = 1000000, M = 2000;

void read(int&);

int main(){
    int n, m;
    static int a[N+5];

    read(n), read(m);

    for(int i = 1; i <= n; i++){
        read(a[i]);
    }

    static int b[M+5];
    int l = 1, r = 0;

    int s = 0;
    while(s<m){
        r++;
        if(!b[a[r]]){
            s++;
        }
        b[a[r]]++;
    }

    while(b[a[l]] > 1){
        b[a[l]]--;
        l++;
    }

    int res = r-l+1;

    int ans_l = l, ans_r = r;

    while(r <= n){
        r++;
        b[a[r]]++;
        while(b[a[l]] > 1){
            b[a[l]]--;
            l++;
        }
        if(r-l+1 < res){
            res = r-l+1;
            ans_l = l, ans_r = r;
        }
        //        res = min(res, r-l+1);
    }

    printf("%d %d\n", ans_l, ans_r);

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c =  getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}
 */