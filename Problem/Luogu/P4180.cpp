//
// Created by kibi on 2022/5/12.
//
// 70pts(100pts在下面)
/*
#include <bits/stdc++.h>
using namespace std;
struct node{
    long long x,y,w,f;
    // bool operator < (const node &b)const{
    //     return w < b.w;
    // }
};
bool cmp(node a, node b){
    return a.w < b.w;
}

node e[300005];
vector<node> v[100005];
long long depth[100005];
long long n, m;
long long d[100005][21];
long long dd[100005][21];
long long fa[100005][21];
long long b[100005];
long long s1;
long long s2 = 9999999999;
int cd(int t1, int t2, int t3, int t4, int mx){
    int ans = 0;
    t1 = t1==mx?0:t1;
    t2 = t2==mx?0:t2;
    t3 = t4==mx?0:t3;
    t4 = t4==mx?0:t4;
    ans = max(t1, max(t2, max(t3, t4)));
    ans = ans==0?mx:ans;
    return ans;
}
int cd2(int t1, int t2, int t3, int t4, int t5, int t6, int mx){
    int ans = 0;
    t1 = t1==mx?0:t1;
    t2 = t2==mx?0:t2;
    t3 = t4==mx?0:t3;
    t4 = t4==mx?0:t4;
    t5 = t5==mx?0:t5;
    t6 = t6==mx?0:t6;
    ans = max(t1, max(t2, max(t3, max(t5, max(t4, t6)))));
    ans = ans==0?mx:ans;
    return ans;
}
node lca(int x, int y){
    if(depth[x]<depth[y]){
        swap(x, y);
    }
    long long mx = 0, mmx = 0;
    for(int i = 18; i >= 0; i--){
        if(fa[x][i]!=0&&depth[fa[x][i]]>=depth[y]){
            x = fa[x][i];
            mmx = cd(mmx, dd[x][i], mx, d[x][i], max(d[x][i], mx));
            //            mmx = max(min(mx, d[x][i]), max(mmx, dd[x][i]));
            mx = max(d[x][i], mx);

        }
    }
    if(x == y){
        return {mx,mmx};
    }
    for(int i = 18; i >= 0; i--){
        if(fa[x][i]!=0&&fa[y][i]!=0&&fa[x][i]!=fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
            mmx = cd2(mmx, dd[x][i], dd[y][i], mx, d[x][i], d[y][i], max(max(d[x][i], d[y][i]), mx));
            //            mmx = max(min(mx, d[x][i]), max(mmx, dd[x][i]));
            mx = max(d[x][i], mx);
            //            mmx = max(min(mx, d[y][i]), max(mmx, dd[y][i]));
            mx = max(d[y][i], mx);

        }
    }
    //    return {max(mx, max(d[x][0], d[y][0])),max(max(min(mx, d[x][0]), max(mmx, dd[x][0])), max(min(mx, d[y][0]), max(mmx, dd[y][0])))};
    return {max(mx, max(d[x][0], d[y][0])),cd2(mmx, dd[x][0], dd[y][0], mx, d[x][0], d[y][0], max(max(d[x][0], d[y][0]), mx))};

}
int find(int x){
    if(b[x] == x){
        return x;
    }
    b[x] = find(b[x]);
    return b[x];
}
void f(int x, int fat, long long dep, long long w){
    fa[x][0] = fat;
    d[x][0] = w;
    dd[x][0] = 0;
    depth[x] = dep;
    int t = v[x].size();
    for(int i = 0; i < t; i++){
        if(v[x][i].y == fat){
            continue;
        }
        f(v[x][i].y, x, dep+1, v[x][i].w);
    }
    return;
}
int main(){
    scanf("%lld %lld", &n, &m);
    for(int i = 1; i <= m; i++){
        long long x,y,w;
        scanf("%lld %lld %lld", &x, &y, &w);
        e[i].x = x;
        e[i].y = y;
        e[i].w = w;
        e[i].f = 0;

    }
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    sort(e+1, e+m+1, cmp);
    for(int i = 1; i <= m; i++){
        if(find(e[i].x)==find(e[i].y)){
            continue;
        }
        e[i].f = 1;
        s1 += e[i].w;
        b[find(e[i].x)] = find(e[i].y);
        v[e[i].x].push_back({e[i].x,e[i].y,e[i].w,0});
        v[e[i].y].push_back({e[i].y,e[i].x,e[i].w,0});
    }
    f(1, 0, 1, 0);
    for(int j = 1; j <= 18; j++){
        for(int i = 1; i <= n; i++){
            fa[i][j] = fa[fa[i][j-1]][j-1];
            d[i][j] = max(d[i][j-1],d[fa[i][j-1]][j-1]);
            dd[i][j] = cd(dd[i][j-1], dd[fa[i][j]][j-1], d[i][j-1], d[fa[i][j]][j-1], d[i][j]);
            //            dd[i][j] = max(min(d[i][j-1], d[fa[i][j-1]][j-1]), max(dd[i][j-1], dd[fa[i][j-1]][j-1]));
            //            int t1 = dd[i][j-1], t2 = dd[dd[i][j-1]][j-1], t3 = d[i][j-1], t4 = d[d[i][j-1]][j-1];
            //            t1 = t1==d[i][j]?0:t1;
            //            t2 = t2==d[i][j]?0:t2;
            //            t3 = t4==d[i][j]?0:t3;
            //            t4 = t4==d[i][j]?0:t4;
            //            dd[i][j] = max(t1, max(t2, max(t3, t4)));
            //            dd[i][j] = dd[i][j]==0?d[i][j]:dd[i][j];
        }
    }

    for(int i = 1; i <= m; i++){
        if(e[i].f){
            continue;
        }
        if(e[i].x==e[i].y){
            continue;
        }
        node t = lca(e[i].x, e[i].y);
        if(t.x == e[i].w){
            if(t.y == e[i].w){
                continue;
            }else{
                t.x = t.y;
            }
        }
        s2 = min(s2, (long long)(e[i].w - t.x));
    }
    printf("%lld", s1+s2);
}
 */
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node{
    int u, v;
    long long w;
    bool f;
}g[300005];
int b[300005];
long long mans;
vector<node> sg[300005];
int f[300005][19], dep[300005];
long long mx[300005][19], me[300005][19];

bool cmp(node a, node b){
    return a.w < b.w;
}

int find(int x){
    if(b[x] != x){
        return b[x] = find(b[x]);
    }
    return x;
}

void dfs(int u, int fa){
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    int sa = sg[u].size();
    for(int i = 0; i < sa; i++){
        if(sg[u][i].v == fa){
            continue;
        }
        mx[sg[u][i].v][0] = sg[u][i].w;
        dfs(sg[u][i].v, u);
    }
}

void pre(){
    for(int i = 1; i <= 18; i++){
        for(int j = 1; j <= n; j++){
            f[j][i] = f[ f[j][i-1] ][i-1];
            int topf = f[j][i-1];
            mx[j][i] = max(mx[j][i-1], mx[topf][i-1]);
            me[j][i] = max(me[j][i-1], me[topf][i-1]);
            if(mx[j][i-1] > mx[topf][i-1]){
                me[j][i] = max(me[j][i], mx[topf][i-1]);
            }else if(mx[j][i-1] < mx[topf][i-1]){
                me[j][i] = max(me[j][i], mx[j][i-1]);
            }
        }
    }
}

int lca(int x, int y){
    if(dep[x] < dep[y]){
        swap(x, y);
    }
    for(int i = 18; i >= 0; i--){
        if(dep[ f[x][i] ] >= dep[y]){
            x = f[x][i];
        }
    }
    if(x == y){
        return x;
    }
    for(int i = 18; i >= 0; i--){
        if(f[x][i] != f[y][i]){
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

long long findmax(int x, int l, int v){
    long long ans = 0;
    for(int i = 18; i >= 0; i--){
        if(dep[ f[x][i] ] >= dep[l]){
            if(mx[x][i] == v){
                ans = max(ans, (long long) me[x][i]);
            }else{
                ans = max(ans, (long long) mx[x][i]);
            }
            x = f[x][i];
        }
    }
    return ans;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%d %d %lld", &g[i].u, &g[i].v, &g[i].w);
        if(g[i].u == g[i].v){
            m--;
            i--;
        }
        g[i].f = false;
    }
    sort(g+1, g+1+m, cmp);
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1, tot = 0; i <= m && tot != n-1; i++){
        if(find(g[i].u) != find(g[i].v)){
            b[find(g[i].u)] = find(g[i].v);
            mans += g[i].w;
            g[i].f = true;
            tot++;
            sg[g[i].u].push_back({g[i].u, g[i].v, g[i].w, g[i].f});
            sg[g[i].v].push_back({g[i].v, g[i].u, g[i].w, g[i].f});
        }
    }

    dfs(1,0);
    pre();

    long long ans = 1e18;
    for(int i = 1; i <= m; i++){
        if(g[i].f){
            continue;
        }
        int t1 = lca(g[i].u, g[i].v);
        long long t2 = findmax(g[i].u, t1, g[i].w), t3 = findmax(g[i].v, t1, g[i].w);
        if(max(t2, t3) != g[i].w){
            ans = min(ans, mans + g[i].w - max(t2, t3));
        }
    }
    printf("%lld", ans);

    return 0;
}