//
// Created by kibi on 22-10-6.
//
#include <bits/stdc++.h>
using namespace std;

struct node{
    node(int v, int id){
        this -> v = v, this -> id = id;
    }
    int v, id;
    //    vector<node> *v;
};
int sta[100005], staR = -1;
vector<int> ans, loc;
vector<node> g[100005];
bool inSta[100005], visN[100005], visM[1000005];

void read(int &x);
void f(int u);

int main(){
    int n, m;
    read(n), read(m);
    for(int i = 1; i <= m; i++){
        int u, v, s, t;
        read(u), read(v), read(s), read(t);
        if(s ^ t) {
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
    }

    //    map<vector<node>*, int> y;
    for(int i = 1; i <= n; i++){
        if(g[i].size()%2){
            printf("NIE");
            return 0;
        }
        //        y[&g[i]] = i;
    }
    loc.push_back(0);
    for(int i = 1; i <= n; i++){
        if(!visN[i]){
            f(i);
            if(inSta[i]){
                //                ans.reserve(ans.size() + 1 + staR+1);
                ans.push_back(i);
                while(staR != -1){
                    inSta[sta[staR]] = false;
                    ans.push_back(sta[staR--]);
                }
                loc.push_back(ans.size());
            }
        }
    }
    printf("%d\n", (int)loc.size() - 1);
    for(int i = 1, mxi = loc.size(); i < mxi; i++){
        printf("%d ", loc[i] - loc[i-1] - 1);
        for(int j = loc[i-1], mxj = loc[i]; j < mxj; j++){
            printf("%d ", ans[j]);
        }
        printf("\n");
    }
    return 0;
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
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s * w;
}

void f(int u){
    static int head[100005] = {0};
    visN[u] = true;
    for(int i = head[u], mxi = g[u].size(); i < mxi; i++){
        node *v = &g[u][i];
        if(!visM[v -> id]){
            visM[v -> id] = true;
            head[u] = i+1;
            f(v -> v);
            if(inSta[v -> v]){
                ans.push_back(v -> v);
                while(sta[staR] != v -> v){
                    inSta[sta[staR]] = false;
                    ans.push_back(sta[staR--]);
                }
                ans.push_back(v -> v);
                loc.push_back(ans.size());
            }else{
                sta[++staR] = v -> v;
                inSta[v -> v] = true;
            }
        }
    }
}