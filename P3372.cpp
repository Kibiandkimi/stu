//
// Created by kibi on 2021/8/5.
//
//线段树？
#include <bits/stdc++.h>
using namespace std;
long long n,m,a[100005],b[400005],tag[400005];
void build(int i, int j, int x){
    if(i == j){
        b[x] = a[i];
        return;
    }
    int t = (i+j)/2;
    build(i,t,x*2);build(t+1,j,x*2+1);
    b[x] = b[x*2]+b[x*2+1];
    return;
}

void pushdown(int x, int l, int r){
    if(tag[x]==0)return;
    int mid = (l+r)/2;
    if(l!=r){
        tag[x*2] += tag[x];
        tag[x*2+1] += tag[x];
        b[x*2] += tag[x]*(mid-l+1);
        b[x*2+1] += tag[x]*(r-mid);
    }
    tag[x] = 0;
    return;
}

long long query(int x, int l, int r, int i, int j){
    pushdown(x, l, r);
    if(l == i && r == j){
        return b[x];
    }
    int mid = (l + r)/2;
    if(j <= mid)return query(x*2,l,mid,i,j);
    else if(i > mid)return query(x*2+1,mid+1,r,i,j);
    else{
        long long u = query(x*2,l,mid,i,mid), v = query(x*2+1,mid+1,r,mid+1,j);
        return u+v;
    }
}

void update(int l, int r, int i, int j, int v, int x){
    pushdown(x, l, r);
    if(l == i && r == j){
        tag[x] += v;
        b[x] += v*(r-l+1);
        return;
    }
    int mid = (l+r)/2;
    if(j<=mid)update(l,mid,i,j,v,x*2);
    else if(i > mid)update(mid+1,r,i,j,v,x*2+1);
    else{
        update(l,mid,i,mid,v,x*2);
        update(mid+1,r,mid+1,j,v,x*2+1);
    }
    if(l != r){
        b[x] = b[x*2]+b[x*2+1];
    }
    return;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d ", &a[i]);
    }
    build(1, n, 1);
    for(int i = 1; i <= m; i++){
        int t1,t2,t3;
        scanf("%d %d %d", &t1, &t2, &t3);
        if(t1 == 1){
            int t4;
            scanf("%d", &t4);
            update(1, n, t2, t3, t4, 1);
        }else{
            printf("%lld\n", query(1, 1, n, t2, t3));
        }
    }
}

//分块
/*
#include <bits/stdc++.h>
using namespace std;
int n, m, sq, t, y;
int st[1005], nd[1005], bel[100005];
long long a[100005];
long long sum[1005];
long long mark[1005];

void add(int l, int r, int k){
    if(bel[l] == bel[r]){
        for(int i = l; i <= r; i++){
            a[i] += k;
            sum[bel[i]] += k;
        }
        //        sum[bel[l]] += k*(r-l+1);
    }else{
        for(int i = l; i <= nd[bel[l]]; i++){
            a[i] += k;
            sum[bel[i]] += k;
        }
        //        sum[bel[l]] += (nd[bel[l]]-l+1)*k;
        for(int i = st[bel[r]]; i <= r; i++){
            a[i] += k;
            sum[bel[i]] += k;
        }
        //        sum[bel[r]] += (r-st[bel[r]+1])*k;
        for(int i = bel[l]+1; i < bel[r]; i++){
            mark[i] += k;
        }
    }
}

long long query(int l, int r){
    long long s = 0;
    if(bel[l] == bel[r]){
        for(int i = l; i <= r; i++){
            s += a[i] + mark[bel[i]];
        }
    }else{
        for(int i = l; i <= nd[bel[l]]; i++){
            s += a[i] + mark[bel[i]];
        }
        for(int i = st[bel[r]]; i <= r; i++){
            s += a[i] + mark[bel[i]];
        }
        for(int i = bel[l]+1; i < bel[r]; i++){
            s += sum[i] + mark[i] * (nd[i]-st[i]+1);
        }
    }
    return s;
}

int main(){
    scanf("%d %d", &n, &m);
    y = ((int)sqrt(n)*(int)sqrt(n)!=n);
    sq = sqrt(n)+y;
    t = n/(sq-y);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    for(int i = 1; i <= sq; i++){
        st[i] = t*(i-1)+1;
        nd[i] = min(t*i, n);
        for(int j = st[i]; j <= nd[i]; j++){
            bel[j] = i;
            sum[i] += a[j];
        }
    }

    for(int i = 1; i <= m; i++){
        int tt;
        scanf("%d", &tt);
        if(tt == 1){
            int x,y,k;
            scanf("%d %d %d", &x, &y, &k);
            add(x, y, k);
        }else{
            int x,y;
            scanf("%d %d", &x, &y);
            printf("%lld\n", query(x, y));
        }
    }

    return 0;
}
 */