#include <bits/stdc++.h>
using namespace std;
int n, m, rt, y[80005], in[80005];
long long d[80005], dotVal[80005];
bool vis[80005];
struct node{
    node(int v, int s, int w){
        this -> v = v, this -> s = s, this -> w = w;
    }
    node(){
        v = 0, s = 0, w = 0;
    }
    int v, s, w;
};
vector<node> rg[80005], ng[80005];
node tem[200005];
int temCnt;

void read(int &x);
void read(double &x);
void f(int u);
bool temCmp(node a, node b);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        int u, v, s;
        double r;
        read(u), read(v), read(s), read(r);
        int now = s, res = 0;
        while(now){
            res += now;
            now = (int)((double)now*r);
        }
        rg[u].emplace_back(v, s, res);
    }
    read(rt);
    f(rt);
    for(int i = 1; i <= n; i++){
        for(auto j : rg[i]){
            if(!vis[j.v]){
                continue;
            }
            if(y[i] == y[j.v]){
                dotVal[y[i]] += j.w;
//                ans += j.w;
                continue;
            }
            tem[++temCnt] = {y[i], y[j.v], j.s};
        }
    }
    sort(tem+1, tem+temCnt+1, temCmp);
    for(int i = 1; i <= temCnt; i++){
        if(ng[tem[i].v].empty() || ng[tem[i].v].back().v != tem[i].s){
            ng[tem[i].v].emplace_back(tem[i].s, tem[i].w, tem[i].w);
            in[tem[i].s]++;
        }
        else{
            ng[tem[i].v].back().w = ng[tem[i].v].back().s = max(ng[tem[i].v].back().s, tem[i].w);
        }
    }

    queue<int> q;
    d[y[rt]] = dotVal[y[rt]];
    long long res = d[y[rt]];
    q.push(y[rt]);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto i : ng[u]){
            d[i.v] = max(d[i.v], d[u] + i.s + dotVal[i.v]);
            res = max(res, d[i.v]);
            in[i.v]--;
            if(!in[i.v]){
                q.push(i.v);
            }
        }
    }
    printf("%lld", res);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
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

void read(double &x){
    int c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    c = getchar();
    if(c == '.'){
        x = getchar()-'0';
        x /= 10;
    }else{
        x = 0;
    }
}

void f(int u){
    static stack<int> st;
    static int dfn[80005] = {0}, low[80005] = {0}, cnt = 0, num = 0;
    vis[u] = true;
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    for(auto i : rg[u]){
        if(!dfn[i.v]){
            f(i.v);
            low[u] = min(low[u], low[i.v]);
        }else if(!y[i.v]){
            low[u] = min(low[u], dfn[i.v]);
        }
    }
    if(low[u] == dfn[u]){
        num++;
        while(st.top() != u){
            y[st.top()] = num;
            st.pop();
        }
        y[st.top()] = num;
        st.pop();
    }
}

bool temCmp(node a, node b){
    return a.v != b.v ? a.v < b.v : a.s != b.s ? a.s < b.s : a.w > b.w;
}