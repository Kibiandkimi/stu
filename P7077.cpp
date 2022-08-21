//
// Created by kibi on 2022/8/18.
//
#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
int n, m, Q, cnt1, cnt2, cnt3;
long long r[100005];
int q[100005];
struct node1{
    int p;
    long long v;
}c1[100005];
struct node2{
    long long v;
}c2[100005];
struct node3{
    int len{}, id{};
    vector<int> opt;
}c3[100005];
struct node4{
    long long mul = 1;
    vector<pair<int, long long> > v;
}c4[100005];
pair<int, int> fun[100005];

int in[100005];
vector<int> g[100005];
queue<int> tp_q;
vector<int> tp_res;

void tp(){
    for(int i = 1; i <= cnt3; i++){
        int so = c3[i].opt.size();
        bool vis[100005] = {false};
        for(int j = 0; j < so; j++) {
            int t = c3[i].opt[j];
            if (!vis[fun[t].first] && fun[t].second==3) {
                g[fun[t].first].push_back(fun[i].first);
                in[fun[i].first]++;
                vis[fun[t].first] = true;
            }
        }
    }

    for(int i = 1; i <= m; i++){
        if(!in[i]&&fun[i].second==3){
            tp_q.push(fun[i].first);
        }
    }

    while(!tp_q.empty()){
        int u = tp_q.front();
        tp_q.pop();
        tp_res.push_back(u);
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            if(!(--in[g[u][i]])){
                tp_q.push(g[u][i]);
            }
        }
    }
}

void add_main(){
    fun[m+1] = {++cnt3, 3};
    c3[cnt3].len = Q, c3[cnt3].id = m+1;
    c3[cnt3].opt.reserve(Q+5);
    for(int i = 1; i <= Q; i++){
        c3[cnt3].opt.push_back(q[i]);
    }
    tp_res.push_back(cnt3);
}

void jx(){
    int stp = tp_res.size();
    add_main();
    for(int i = 0; i <= stp; i++){
        int u = tp_res[i];
        int so = c3[u].opt.size();
        vector<int> &uv = c3[u].opt;
        int vis[100005] = {0}, vis_first = 0;
        node4 &out = c4[u];
        vector<long long> mul_now;
        mul_now.reserve(so+4);
        for(int j = so-1; j >= 0; j--){
            int v = uv[j];
            if(fun[v].second==2){
                out.mul = ((out.mul * c2[fun[v].first].v)%mod);
                mul_now.push_back(out.mul);
            }else if(fun[v].second==3){
                mul_now.push_back(out.mul);
                out.mul = ((out.mul * c4[fun[v].first].mul)%mod);
            }else {
                mul_now.push_back(out.mul);
            }
        }
        for(int j = 0; j < so; j++){
            int v = uv[j];
            if(fun[v].second==1){
                node1 &f = c1[fun[v].first];
                if(vis[f.p]||f.p==vis_first){
                    out.v[vis[f.p]].second = (out.v[vis[f.p]].second + mul_now[(so-j-1)]*f.v)%mod;
                }else{
                    out.v.emplace_back(f.p, (mul_now[(so-j-1)]*f.v)%mod);
                    vis[f.p] = out.v.size()-1;
                    if(!vis[f.p]){
                        vis_first = f.p;
                    }
                }
            }else if(fun[v].second==3){
                node4 &f = c4[fun[v].first];
                int ss = f.v.size();
                for(int k = 0; k < ss; k++){
                    if(vis[f.v[k].first]||f.v[k].first==vis_first){
                        out.v[vis[f.v[k].first]].second = (out.v[vis[f.v[k].first]].second + mul_now[(so-j-1)]*f.v[k].second)%mod;
                    }else{
                        //                       out.v.emplace_back({f.v[k].first, (mul_now[j]*f.v[k].second)%mod});
                        out.v.emplace_back(f.v[k].first, (mul_now[(so-j-1)]*f.v[k].second)%mod);
                        vis[f.v[k].first] = out.v.size()-1;
                        if(!vis[f.v[k].first]){
                            vis_first = f.v[k].first;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    //    freopen("t.in", "r", stdin);
    //    freopen("t.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &r[i]);
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        int c;
        scanf("%d", &c);
        if(c == 1){
            fun[i] = {++cnt1, 1};
            int p, v;
            scanf("%d %d", &p, &v);
            c1[cnt1].p = p, c1[cnt1].v = v;
            //            c1[cnt1].id = i;
        }else if(c == 2){
            fun[i] = {++cnt2, 2};
            int v;
            scanf("%d", &v);
            c2[cnt2].v = v;
            //            c2[cnt2].id = i;
        }else if(c == 3){
            fun[i] = {++cnt3, 3};
            int l;
            scanf("%d", &l);
            c3[cnt3].len = l, c3[cnt3].id = i;
            c3[cnt3].opt.reserve(l+4);
            for(int j = 1; j <= l; j++){
                int t;
                scanf("%d", &t);
                c3[cnt3].opt.push_back(t);
            }
        }
    }
    scanf("%d", &Q);
    for(int i = 1; i <= Q; i++){
        scanf("%d", &q[i]);
    }

    tp();
    jx();

    for(int i = 1; i <= n; i++){
        r[i] = (r[i]*c4[cnt3].mul)%mod;
    }
    int ss = c4[cnt3].v.size();
    for(int i = 0; i < ss; i++){
        r[c4[cnt3].v[i].first] = (r[c4[cnt3].v[i].first] + c4[cnt3].v[i].second)%mod;
    }

    for(int i = 1; i <= n; i++){
        printf("%lld ", r[i]);
    }
    //    fclose(stdin);
    //    fclose(stdout);
}