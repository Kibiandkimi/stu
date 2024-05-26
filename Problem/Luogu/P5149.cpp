//
// Created by kibi on 2022/8/4.
//
#include <bits/stdc++.h>
using namespace std;
int n, cnt = 1;
long long ans;
char c[10];
struct node {
    int v = 0;
    int son[52] = {0};
} tr[500005];
int g[100005];

int h(char s) {
    if ('a' <= s && s <= 'z') {
        return s - 'a';
    } else {
        return s - 'A' + 26;
    }
}

void insert(int id) {
    int u = 1;
    for (int i = 1; c[i] != 0; i++) {
        //        if (!tr[u].son[h(c[i])]){
        //            tr[u].son[h(c[i])] = ++cnt;
        //        }
        //        u = tr[u].son[h(c[i])];
        int &t = tr[u].son[h(c[i])];
        u = t = t?t:++cnt;
    }
    tr[u].v = id;
}

int query(){
    int u = 1;
    for(int i = 1; c[i] != 0; i++){
        u = tr[u].son[h(c[i])];
    }
    return tr[u].v;
}

void gb(int l, int r){
    if(l == r){
        return ;
    }
    int mid = (l+r)/2;
    gb(l, mid);
    gb(mid+1, r);
    int i = l, j = mid+1, t[100005], cnt = 1;
    while(i <= mid && j <= r){
        if(g[i] < g[j]){
            t[cnt++] = g[i];
            i++;
        }else{
            ans += mid-i+1;
            t[cnt++] = g[j];
            j++;
        }
    }
    while(j <= r){
        t[cnt++] = g[j];
        j++;
    }
    while(i <= mid){
        t[cnt++] = g[i];
        i++;
    }
    for(int k = l; k <= r; k++){
        g[k] = t[k-l+1];
    }
}

int main() {
    scanf("%d", &n);
    memset(tr, 0, sizeof tr);
    for (int i = 1; i <= n; i++) {
        scanf("%s", c + 1);
        insert(i);
    }
    for(int i = 1; i <= n; i++){
        scanf("%s", c+1);
        g[i] = query();
    }
    gb(1, n);
    printf("%lld", ans);
}