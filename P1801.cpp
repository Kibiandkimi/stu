//
// Created by kibi on 2022/8/5.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, val[200005], rnk[200005], son[200005][2], siz[200005], sum_p;
int x1[200005], flag[200005];

int NewNode(int x){
    ++sum_p;
    siz[sum_p] = 1;
    val[sum_p] = x;
    rnk[sum_p] = rand();
    return sum_p;
}

void update(int x){
    siz[x] = siz[son[x][0]]+siz[son[x][1]]+1;
}

void splite(int &x, int &y, int k, int pos){
    if(pos){
        if(val[pos] <= k){
            x = pos;
            splite(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            splite(x, son[pos][0], k, son[pos][0]);
        }
        update(pos);
    }else{
        x=y=0;
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }
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

int find(int pos, int rank){
    while(true){
        if(siz[son[pos][0]] >= rank){
            pos = son[pos][0];
        }else{
            if(siz[son[pos][0]]+1 == rank){
                return pos;
            }else{
                rank -= siz[son[pos][0]]+1;
                pos = son[pos][1];
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    srand((unsigned)time(nullptr));
    for(int i = 1; i <= n; i++){
        scanf("%d", &x1[i]);
    }
    for(int i = 1; i <= m; i++){
        int t;
        scanf("%d", &t);
        flag[t]++;
    }
    int x, y;
    int root = 0;
    int pos = 0;
    for(int i = 1; i <= n; i++){
        splite(x, y, x1[i], root);
        root = merge(merge(x, NewNode(x1[i])), y);
        while(flag[i]){
            pos++;
            flag[i]--;
            printf("%d\n", val[find(root, pos)]);
        }
    }

}