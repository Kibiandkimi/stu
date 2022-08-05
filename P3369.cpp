//
// Created by kibi on 2022/8/5.
//
#include <bits/stdc++.h>
using namespace std;
int n, root;
int val[100005], rnk[100005], siz[100005], son[100005][2], cnt, num[100005];

int new_node(int x){
    val[++cnt] = x;
    rnk[cnt] = rand();
    siz[cnt] = 1;
    num[cnt] = 1;
    return cnt;
}

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void splite(int &x, int &y, int k, int pos){
    if(!pos){
        x = 0, y = 0;
    }else{
        if(val[pos] <= k){
            x = pos;
            splite(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            splite(x, son[pos][0], k, son[pos][0]);
        }
        update(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(rnk[x] < rnk[y]){
            son[x][1] = merge(son[x][1], y);
            update(x);
            return x;
        }else{
            son[y][0] = merge(x, son[y][0]);
            update(y);
            return y;
        }
    }
}

void insert(int x){
    int l, r;
    splite(l, r, x, root);
    int tl = 0, tr = 0;
    splite(tl, tr, x-1, l);
    if(!tr){
        //        merge(merge(l, new_node(x)), r);
        root = merge(merge(tl, new_node(x)), r);
    }else{
        num[tr]++;
        update(tr);
        root = merge(merge(tl, tr), r);
    }

}

void del(int x){
    int l, r;
    splite(l, r, x, root);
    int tl = 0, tr = 0;
    splite(tl, tr, x-1, l);
    if(num[tr]>1){
        num[tr]--;
        update(tr);
        merge(tl, tr);
    }else{
        if(l == tr){
            l = 0;
        }

    }
}

int query_rk(int x){

}

int query_x(int x){

}

int query_pre(int x){

}

int query_nxt(int x){

}

int main(){
    srand((unsigned)time(nullptr));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int op, x;
        scanf("%d %d", &op, &x);
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                printf("%d\n", query_rk(x));
                break;
            case 4:
                printf("%d\n", query_x(x));
                break;
            case 5:
                printf("%d\n", query_pre(x));
                break;
            case 6:
                printf("%d\n", query_nxt(x));
        }
    }
}