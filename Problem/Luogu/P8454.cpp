//
// Created by kibi on 22-9-20.
//
#include <bits/stdc++.h>
using namespace std;
struct Question{
    int l, h, il[5], ih[7], w, id;
}Q[100005];
struct Tree{
    int l, r, ls, rs;
    long long mx, mn, tag;
}tr[400005];
struct Line{
    int opt, w, x;
}line[400005];

void read(int &x);
bool cmpQ(Question a, Question b);
bool cmpL(Line a, Line b);
void build(int u, int l, int r, const long long *s);
void update(int u, int l, int w);
long long queryMin(int u, int l, int r);
long long queryMax(int u, int l, int r);
long long queryX(int u, int x);
void pushDown(int u);
void pushUp(int u);

int main(){
    int S, n, q, w, b1, b2, inc, dec, cnt = 0, pos = 1, x[100005];
    long long qz[100005], Ans[100005];
    scanf("%d %d %d %d %d %d %d %d", &S, &n, &q, &w, &b1, &b2, &inc, &dec);
    //    queue<int> line;
    for(int i = 1; i <= n; i++){
        read(x[i]);
        line[(i-1)*4+1] = {1, x[i]-b2, i};
        line[(i-1)*4+2] = {2, x[i]-b1, i};
        line[(i-1)*4+3] = {3, x[i]+b1+1, i};
        line[(i-1)*4+4] = {4, x[i]+b2+1, i};
        qz[i] = qz[i-1] + dec;
    }
    for(int i = 1; i <= q; i++){
        int op;
        read(op);
        if(op == 1){
            int l, h;
            read(l), read(h);
            cnt++;
            Q[cnt].id = cnt, Q[cnt].l = l, Q[cnt].h = h+2;
            for(int j = 0; j < l; j++){
                read(Q[cnt].il[j]);
            }
            for(int j = 0; j < h; j++){
                read(Q[cnt].ih[j]);
            }
            //            note3?
            Q[cnt].ih[h] = n+1;
            Q[cnt].ih[h+1] = 0;
            Q[cnt].w = w;
            sort(Q[cnt].il, Q[cnt].il+l);
            sort(Q[cnt].ih, Q[cnt].ih+h+2);
        }else{
            read(w);
        }
    }
    sort(Q+1, Q+1+cnt, cmpQ);
    sort(line+1, line+n*4+1, cmpL);
    build(1, 0, n, qz);
    for(int i = 1; i <= cnt; i++){
        w = Q[i].w;
        //        note2
        while(pos<=n*4&&line[pos].w<=w){
            update(1, line[pos].x, line[pos].opt==1?(-dec):line[pos].opt==2?inc:line[pos].opt==3?(-inc):dec);
            pos++;
        }
        int p1 = 0, p2 = 0;
        long long ans = -1e18;
        while(p2<Q[i].l){
            while(Q[i].ih[p1+1]<Q[i].il[p2]){
                p1++;
            }
            //            note1
            long long int nowNum = queryX(1, Q[i].il[p2]);
            //            bool flag1 = Q[i].il[p2] - Q[i].ih[p1] > 1;
            long long int frontMin = queryMin(1, Q[i].ih[p1], Q[i].il[p2] - 1);
            //            bool flag2 = Q[i].ih[p1 + 1] - Q[i].il[p2] > 1;
            long long int backMax = queryMax(1, Q[i].il[p2], Q[i].ih[p1 + 1] - 1);
            ans = max(ans, (nowNum - frontMin) + (backMax - nowNum));
            p2++;
        }
        Ans[Q[i].id] = ans;
    }
    for(int i = 1; i <= cnt; i++){
        printf("%lld\n", Ans[i]);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

bool cmpQ(Question a, Question b){
    return a.w < b.w;
}

bool cmpL(Line a, Line b) {
    return a.w < b.w;
}

void build(int u, int l, int r, const long long *s) {
    tr[u].l = l, tr[u].r = r, tr[u].tag = 0;
    if(l == r) {
        tr[u].mx = tr[u].mn = s[l];
        return;
    }
    int mid = (l+r)>>1;
    tr[u].ls = u*2, tr[u].rs = u*2+1;
    build(tr[u].ls, l, mid, s);
    build(tr[u].rs, mid+1, r, s);
    pushUp(u);
}

void update(int u, int l, int w) {
    if(tr[u].l == tr[u].r){
        tr[u].mx += w;
        tr[u].mn += w;
        return ;
    }
    if(tr[u].l>=l){
        tr[u].tag += w;
        tr[u].mn += w;
        tr[u].mx += w;
        return ;
    }
    pushDown(u);
    if(tr[tr[u].ls].r>=l){
        update(tr[u].ls, l, w);
    }
    update(tr[u].rs, l, w);
    pushUp(u);
}

long long queryMin(int u, int l, int r) {
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].mn;
    }
    pushDown(u);
    long long ans = 1e18;
    if(tr[tr[u].ls].r>=l){
        ans = min(ans, queryMin(tr[u].ls, l, r));
    }
    if(tr[tr[u].rs].l<=r){
        ans = min(ans, queryMin(tr[u].rs, l, r));
    }
    return ans;
}

long long queryMax(int u, int l, int r){
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].mx;
    }
    pushDown(u);
    long long ans = -1e18;
    if(tr[tr[u].ls].r>=l){
        ans = max(ans, queryMax(tr[u].ls, l, r));
    }
    if(tr[tr[u].rs].l<=r){
        ans = max(ans, queryMax(tr[u].rs, l, r));
    }
    return ans;
}

long long queryX(int u, int x){
    if(tr[u].l == tr[u].r){
        return tr[u].mn;
    }
    pushDown(u);
    if(tr[tr[u].ls].r>=x){
        return queryX(tr[u].ls, x);
    }
    return queryX(tr[u].rs, x);
}

void pushDown(int u) {
    if(tr[u].tag){
        int ls = tr[u].ls, rs = tr[u].rs;
        tr[ls].tag += tr[u].tag;
        tr[ls].mn += tr[u].tag;
        tr[ls].mx += tr[u].tag;
        tr[rs].tag += tr[u].tag;
        tr[rs].mn += tr[u].tag;
        tr[rs].mx += tr[u].tag;
        tr[u].tag = 0;
    }
}

void pushUp(int u) {
    tr[u].mn = min(tr[tr[u].ls].mn, tr[tr[u].rs].mn);
    tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
}
