#include <bits/stdc++.h>
using namespace std;
#define int long long
long long n, m;

void read(long long &x);
bool get_type(long long c);

struct node{
    int l, r, ls, rs;
    long long s, tag;
}tr[400005];
long long a[100005];
int siz[100005], fa[100005]/*, dep[100005]*/, son[100005];
int top[100005], id[100005], rnk[100005], last[100005], cnt;
vector<int> g[100005];
void f1(int u);
void f2(int u, int t);
void build(int u, int l, int r);
void push_down(int u);
long long query(int u, int l, int r);
void update(int u, int l, int r, long long k);
void op1(int x, long long k);
void op2(int x, long long k);
long long op3(int x);

signed main(){
    //#define read(a) scanf("%lld", &a)
    read(n);
    read(m);
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    for(int i = 1; i < n; i++){
        long long from, to;
        read(from);
        read(to);
        g[from].push_back((int)to);
        g[to].push_back((int)from);
    }
    f1(1);
    f2(1, 1);
    build(1, 1, (int)n);
    while(m--){
        long long opt;
        read(opt);
        if(opt == 1){
            long long x, k;
            read(x), read(k);
            op1((int)x, k);
        }else if(opt == 2){
            long long x, k;
            read(x), read(k);
            op2((int)x, k);
        }else if(opt == 3){
            long long x;
            read(x);
            long long ans = op3((int)x);
            printf("%lld\n", ans);
        }
    }

}
//#define read(a) read(a)

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(get_type(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!get_type(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}
bool get_type(long long c) { return c<'0'||'9'<c; }

void f1(int u){
    int sg = g[u].size();
    //    dep[u] = dep[fa[u]]+1;
    siz[u] = 1;
    for(int i = 0; i < sg; i++){
        if(g[u][i] != fa[u]){
            fa[g[u][i]] = u;
            f1(g[u][i]);
            siz[u] += siz[g[u][i]];
            if(siz[g[u][i]] > siz[son[u]]){
                son[u] = g[u][i];
            }
        }
    }
}

void f2(int u, int t){
    top[u] = t;
    id[u] = ++cnt;
    rnk[cnt] = u;
    if(!son[u]){
        last[u] = cnt;//啊啊，这个我调了一下午
        return;
    }
    f2(son[u], t);
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!id[g[u][i]] && fa[u]!=g[u][i]){
            f2(g[u][i], g[u][i]);
        }
    }
    last[u] = cnt;
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u]. r = r, tr[u].tag = 0;
    if(l == r){
        tr[u].ls = tr[u].rs = 0;
        tr[u].s = a[rnk[l]];
        return ;
    }
    int mid = (l+r)/2;
    build(u*2, l, mid);
    build(u*2+1, mid+1, r);
    tr[u].ls = u*2;
    tr[u].rs = u*2+1;
    tr[u].s = tr[tr[u].ls].s + tr[tr[u].rs].s;
}

void push_down(int u){
    if(tr[u].tag){
        tr[tr[u].ls].tag += tr[u].tag;
        tr[tr[u].ls].s += (tr[tr[u].ls].r - tr[tr[u].ls].l + 1) * tr[u].tag;
        tr[tr[u].rs].tag += tr[u].tag;
        tr[tr[u].rs].s += (tr[tr[u].rs].r - tr[tr[u].rs].l + 1) * tr[u].tag;
        tr[u].tag = 0;
    }
}

long long query(int u, int l, int r){
    if(l<=tr[u].l&&tr[u].r<=r){
        return tr[u].s;
    }
    push_down(u);
    long long ans = 0;
    if(l <= tr[tr[u].ls].r){
        ans += query(tr[u].ls, l, r);
    }
    if(r >= tr[tr[u].rs].l){
        ans += query(tr[u].rs, l, r);
    }
    return ans;
}

void update(int u, int l, int r, long long k){
    if(tr[u].l == tr[u].r){
        tr[u].s += k;
        return ;
    }
    if(l<=tr[u].l && tr[u].r<=r){
        tr[u].tag += k;
        //        tr[u].s += (tr[u].r-tr[u].l+1)*k;
        tr[u].s = tr[tr[u].ls].s + tr[tr[u].rs].s + (tr[u].r-tr[u].l+1)*tr[u].tag;
        return ;
    }
    push_down(u);
    if(l <= tr[tr[u].ls].r){
        update(tr[u].ls, l, r, k);
    }
    if(r >= tr[tr[u].rs].l){
        update(tr[u].rs, l, r, k);
    }
    tr[u].s = tr[tr[u].ls].s + tr[tr[u].rs].s + (tr[u].r-tr[u].l+1)*tr[u].tag;
}

void op1(int x, long long k){
    x = id[x];
    update(1, x, x, k);
}

void op2(int x, long long k){
    update(1, id[x], last[x], k);
}

long long op3(int x){
    long long ans = 0;
    while(top[x]){
        ans += query(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    return ans;
}