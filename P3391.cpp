//
// Created by kibi on 22-8-9.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, root;
int val[100005], rnk[100005], son[100005][2], siz[100005];
bool flag[100005];

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void push_down(int x){
    if(flag[x]){
        swap(son[x][0], son[x][1]);
        flag[son[x][0]] ^= 1;
        flag[son[x][1]] ^= 1;
        flag[x] = false;
    }
}

int new_node(int x){
    val[++cnt] = x;
    rnk[cnt] = rand();
    siz[cnt] = 1;
    return cnt;
}

void split(int &x, int &y, int k, int pos){
    if(!pos){
        x = y = 0;
    }else{
        push_down(pos);
        if(siz[son[pos][0]] >= k){
            y = pos;
            split(x, son[pos][0], k, son[pos][0]);
            update(y);
        }else{
            x = pos;
            split(son[pos][1], y, k-siz[son[pos][0]]-1, son[pos][1]);
            update(x);
        }
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(rnk[x] < rnk[y]){
            push_down(x);
            son[x][1] = merge(son[x][1], y);
            update(x);
            return x;
        }else{
            push_down(y);
            son[y][0] = merge(x, son[y][0]);
            update(y);
            return y;
        }
    }
}

void f(int pos){
    push_down(pos);
    if(son[pos][0]){
        f(son[pos][0]);
    }
    printf("%d ", val[pos]);
    if(son[pos][1]){
        f(son[pos][1]);
    }
}


int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        root = merge(root, new_node(i));
    }
    for(int i = 1; i <= m; i++){
        // f(root);
        int l, r;
        scanf("%d %d", &l, &r);
        int x, y, z;
        split(x, y, l-1, root);
        split(y, z, r-l+1, y);
        flag[y] ^= 1;
        root = merge(x, merge(y, z));
        // printf("\n");
    }
    f(root);
}