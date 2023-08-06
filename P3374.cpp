//
// Created by kibi on 2021/8/5.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[500005],b[500005];
int lowbit(int x){ return x & -x;}
int update(int x, int v){
    while(x <= n){
        b[x] += v;
        x += lowbit(x);
    }
    return 0;
}
int query(int x){
    int res = 0;
    while(x > 0){
        res += b[x];
        x -= lowbit(x);
    }
    return res;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        update(i, a[i]);
    }
    for(int i = 1; i <= m; i++){
        int t1,t2,t3;
        scanf("%d %d %d", &t1, &t2, &t3);
        if(t1 == 1){
            update(t2, t3);
        }else{
            printf("%d\n", query(t3)-query(t2-1));
        }
    }

}

// 2023/8/1
/*
#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

void read(int&);

int main(){
    class TreeArray{
        int data[4 * N + 5]{}, n;
    public:
        TreeArray(int n):n(n){}
        void add(int x, int v){
            while(x <= n){
                data[x] += v;
                x += (x&-x);
            }
        }
        int query(int x){
            int ans = 0;
            while(x){
                ans += data[x];
                x -= (x&-x);
            }
            return ans;
        }
    };

    int n, m;
    read(n), read(m);

    TreeArray tree(n);

    for(int i = 1; i <= n; i++){
        int t;
        read(t);
        tree.add(i, t);
    }

    for(int i = 1; i <= m; i++){
        int opt, x, y;
        read(opt), read(x), read(y);
        if(opt == 1){
            tree.add(x, y);
        }else{
            printf("%d\n", tree.query(y)-tree.query(x-1));
        }
    }
}

void read(int& x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}
*/