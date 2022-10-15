//
// Created by kibi on 2022/10/13.
//
#include <bits/stdc++.h>
using namespace std;
class SegTree{
    static const int Size = 150005;
    int val[Size]{}, ls[Size]{}, rs[Size]{}, ll[Size]{}, rr[Size]{};
    void build(int u, int l, int r, const int* arr){
        ll[u] = l, rr[u] = r;
        if(l == r){
            val[u] = arr[l];
            return ;
        }
        int mid = (l+r)/2;
        ls[u] = u*2, rs[u] = u*2 + 1;
        build(ls[u], l, mid, arr);
        build(rs[u], mid+1, r, arr);
        val[u] = max(val[ls[u]], val[rs[u]]);
    }
    int queryMax(int u, int l, int r){
        if(l <= ll[u] && rr[u] <= r){
            return val[u];
        }
        int ans = -1e9;
        if(rr[ls[u]] >= l){
            ans = max(ans, queryMax(ls[u], l, r));
        }
        if(ll[rs[u]] <= r){
            ans = max(ans, queryMax(rs[u], l, r));
        }
        return ans;
    }
public:
    SegTree(int size, int* val){
        build(1, 1, size, val);
    }
    int queryMax(int l, int r){
        if(l > r){
            //            TODO solve this problem, because it can't be (l > r), it is an error.
            return 0;
        }
        return queryMax(1, l, r);
    }
};

int find(int x, int l, int r, const int* arr);
void read(int &x);

int main(){
    int n;
    static int rawYear[50005] = {0}, rawRain[50005] = {0};
    read(n);
    for(int i = 1; i <= n; i++){
        read(rawYear[i]), read(rawRain[i]);
    }
    static SegTree tree(n, rawRain);
    rawYear[n+1] = 1000000005;
    int m;
    read(m);
    while(m--){
        int x, y;
        read(y), read(x);
        int u = find(y, 1, n+1, rawYear), v = find(x, 1, n+1, rawYear), ans = 0;
        if(rawYear[v] == x && rawYear[u] == y){
            if(rawRain[u] < rawRain[v]){
                ans = -1;
            }else if(v == u+1){
                if(x == y+1){
                    ans = 1;
                }
                /*
                 * else{
                 * ans = 0;
                 * }
                 * */
            }else{
                int mx = tree.queryMax(u+1, v-1);
                if(mx >= rawRain[v]){
                    ans = -1;
                }else{
                    if(x - y == v - u){
                        ans = 1;
                    }
                    /*
                     * else{
                     * ans = 0;
                     * }
                     * */
                }
            }
        }else if(rawYear[v] == x && rawYear[u] != y){
            /*
             * if(u == v){
             *      ans = 0;
             * }
             * */
            int mx = tree.queryMax(u, v-1);
            if(mx >= rawRain[v]){
                ans = -1;
            }/*
            * else{
            * ans = 0
            * }
            * */
        }else if(rawYear[v] != x && rawYear[u] == y){
            /*
             * if(v == u+1){
             *      ans = 0;
             * }
             * */
            int mx = tree.queryMax(u+1, v-1);
            if(rawRain[u] <= mx){
                ans = -1;
            }/*
            * else{
            *       ans = 0;
            * }
            * */
        }/*else //if(rawYear[u] != y && rawYear[v] != x){
            ans = 0
        }
        */
        ans == 1 ? printf("true\n") : ans == -1 ? printf("false\n") : printf("maybe\n");
    }
}

int find(int x, int l, int r, const int* arr){
    while(l < r){
        int mid = (l+r)/2;
        if(x <= arr[mid]){
            r = mid;
        }else{
            l = mid+1;
        }
    }
    return l;
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
        c = getchar();
    }
    x = s * w;
}