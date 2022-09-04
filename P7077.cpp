//
// Created by kibi on 2022/8/18.
//
#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
int n, m, Q, cnt1, cnt2, cnt3;
long long r[100005];
int q[100005];
int len3[100005], y[100005];
struct node1{
    int p;
    long long v;
}c1[100005];
struct node2{
    long long v;
}c2[100005];
struct node3{
    //    int id = -1;
    vector<int> opt;
}c3[100005];
struct node4{
    long long mul = 1;
    vector<int> p;
    vector<long long> v;
    //    vector<pair<int, long long> > v;
}c4[100005];
struct Func{
    int id, type;
};
Func func[100005];
vector<int> tp_res;

void tp(){
    int in[100005];
    vector<int> g[100005];
    queue<int> tp_q;
    int vis[100005] = {0};
    for(int i = 1; i <= cnt3; i++){
        g[i].reserve(len3[y[i]]+2);
    }
    for(int i = 1; i <= cnt3; i++){
        int so = c3[i].opt.size();
        for(int j = 0; j < so; j++) {
            int t = c3[i].opt[j];
            if ((vis[func[t].id]!=i) && func[t].type==3) {
                //                g[func[t].id].push_back(func[i].id);
                g[func[t].id].push_back(i);
                //                in[func[i].id]++;
                in[i]++;
                vis[func[t].id] = i;
            }
        }
    }

    //    for(int i = 1; i <= m; i++){
    //        if(!in[i]&& func[i].type==3){
    //            tp_q.push(func[i].id);
    //        }
    //    }
    for(int i = 1; i <= cnt3; i++){
        if(!in[i]){
            tp_q.push(i);
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
    func[m+1] = {++cnt3, 3};
    //    c3[cnt3].len = Q,
    //    c3[cnt3].id = m+1;
    c3[cnt3].opt.reserve(Q+5);
    for(int i = 1; i <= Q; i++){
        c3[cnt3].opt.push_back(q[i]);
    }
    tp_res.push_back(cnt3);
}

void jx(){
    int stp = tp_res.size();
    add_main();
    int y[100005] = {0}, vis[100005] = {0};
    long long mul_now[1000005];
    for(int i = 0; i <= stp; i++){
        int u = tp_res[i];
        int so = c3[u].opt.size();
        vector<int> &opt = c3[u].opt;
        int vis_first = 0, cnt = 0;
        node4 &out = c4[u];
        //        vector<long long> mul_now;
        //        mul_now.reserve(so+4);
        for(int j = so-1; j >= 0; j--){
            int v = opt[j];
            if(func[v].type==2){
                out.mul = ((out.mul * c2[func[v].id].v)%mod);
                mul_now[cnt++] = out.mul;
            }else if(func[v].type==3){
                //                mul_now.push_back(out.mul);
                mul_now[cnt++] = out.mul;
                out.mul = ((out.mul * c4[func[v].id].mul)%mod);
            }else {
                mul_now[cnt++] = out.mul;
                //                mul_now.push_back(out.mul);
            }
        }
        for(int j = 0; j < so; j++){
            int v = opt[j];
            if(func[v].type==1){
                node1 &f = c1[func[v].id];
                if((y[f.p]||f.p==vis_first)&&vis[f.p]==i){
                    out.v[y[f.p]] = (out.v[y[f.p]] + mul_now[(so-j-1)]*f.v)%mod;
                    //                    out.v[y[f.p]].second = (out.v[y[f.p]].second + mul_now[(so-j-1)]*f.v)%mod;
                }else{
                    //                    out.v.emplace_back(f.p, (mul_now[(so-j-1)]*f.v)%mod);
                    out.v.push_back((mul_now[(so-j-1)]*f.v)%mod);
                    out.p.push_back(f.p);
                    y[f.p] = out.v.size()-1;
                    vis[f.p] = i;
                    if(!y[f.p]){
                        vis_first = f.p;
                    }
                }
            }else if(func[v].type==3){
                node4 &f = c4[func[v].id];
                int ss = f.v.size();
                for(int k = 0; k < ss; k++){
                    if((y[f.p[k]]||f.p[k]==vis_first)&&vis[f.p[k]]==i){
                        out.v[y[f.p[k]]] = (out.v[y[f.p[k]]] + mul_now[(so-j-1)]*f.v[k])%mod;
                    }else{
                        //                        out.v.emplace_back(f.p[k], (mul_now[(so-j-1)]*f.v[k])%mod);
                        out.v.push_back((mul_now[(so-j-1)]*f.v[k])%mod);
                        out.p.push_back(f.p[k]);
                        vis[f.p[k]] = i;
                        y[f.p[k]] = out.v.size()-1;
                        if(!y[f.p[k]]){
                            vis_first = f.p[k];
                        }
                    }
                }
//                TODO 尝试释放c4的vector
//                --len4[y[func[v].id]];
//                if(!len4[y[func[v].id]]){
//                    vector<int>().swap(c4[func[v].id].p);
//                    vector<long long>().swap(c4[func[v].id].v);
//                }
            }
        }
        vector<int>().swap(c3[u].opt);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(r[i]);
    }
    read(m);
    int vis[100005] = {0};
    for(int i = 1; i <= m; i++){
        int c;
        read(c);
        if(c == 1){
            func[i] = {++cnt1, 1};
            int p, v;
            read(p), read(v);
            c1[cnt1].p = p, c1[cnt1].v = v;
        }else if(c == 2){
            func[i] = {++cnt2, 2};
            int v;
            read(v);
            c2[cnt2].v = v;
        }else if(c == 3){
            func[i] = {++cnt3, 3};
            int l;
            read(l);
            c3[cnt3].opt.reserve(l+4);
            y[cnt3] = i;
            for(int j = 1; j <= l; j++){
                int t;
                read(t);
                if(func[t].type==3&& vis[t]!=i){
                    vis[t] = i;
                    len3[t]++;
                }
                c3[cnt3].opt.push_back(t);
            }
        }
    }
    read(Q);
    for(int i = 1; i <= Q; i++){
        read(q[i]);
    }

    tp();
    jx();

    for(int i = 1; i <= n; i++){
        r[i] = (r[i]*c4[cnt3].mul)%mod;
    }
    int ss = c4[cnt3].v.size();
    for(int i = 0; i < ss; i++){
        r[c4[cnt3].p[i]] = (r[c4[cnt3].p[i]] + c4[cnt3].v[i])%mod;
    }

    for(int i = 1; i <= n; i++){
        printf("%lld ", r[i]);
    }
}