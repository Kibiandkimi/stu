//
// Created by kibi on 2021/10/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, S = 1, cnt[2];
bool flag = 1;
int del[100005];
int du[100005][2];
stack<int> st;
vector<int> a[100005];
void f(int x){
    int sa = a[x].size();
    for(int i = del[x]; i < sa; i=del[x]){
        del[x] = i+1;
        f(a[x][i]);
    }
    st.push(x);
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        du[u][1]++;
        du[v][0]++;
    }
    for(int i = 1; i <= n; i++){
        sort(a[i].begin(), a[i].end());
    }
    for(int i = 1; i <= n; i++){
        if(du[i][1] != du[i][0]){
            flag = 0;
        }
        if(du[i][1]-du[i][0]==1){
            cnt[1]++;
            S = i;
        }
        if(du[i][0]-du[i][1]==1){
            cnt[0]++;
        }
    }
    if((!flag)&&!(cnt[0]==cnt[1]&&cnt[0]==1)){
        printf("No");
        return 0;
    }
    f(S);
    while(!st.empty()){
        int t = st.top();
        st.pop();
        printf("%d ", t);
    }
}

namespace Second{
    //
    // Created by kibi on 2022/10/28.
    //
    using namespace std;

    int n, m, in[100005], out[100005], nxt[100005];
    vector<int> g[100005];
    stack<int> sta;

    void read(int &x);
    void f(int u);

    int main(){
        read(n), read(m);
        for(int i = 1; i <= m; i++){
            static int u, v;
            read(u), read(v);
            g[u].emplace_back(v);
            ++in[v];
            ++out[u];
        }
        for(int i = 1; i <= n; i++){
            sort(g[i].begin(), g[i].end());
        }
        bool flag = true;
        static int tem1, tem2, st = 1;
        for(int i = 1; i <= n; i++){
            if(in[i] != out[i]){
                flag = false;
            }
            if(in[i] - out[i] == 1){
                ++tem1;
            }
            if(out[i] - in[i] == 1){
                ++tem2;
                st = i;
            }
        }
        if((!flag) && (tem1!=1||tem2!=1)){
            printf("No");
            return 0;
        }
        f(st);
        while(!sta.empty()){
            printf("%d ", sta.top());
            sta.pop();
        }
    }

    void read(int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            if(c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

    void f(int u){
        for(int i = nxt[u], mxi = g[u].size(); i < mxi; i = nxt[u]){
            nxt[u] = i+1;
            f(g[u][i]);
        }
        sta.push(u);
    }
}