//
// Created by kibi on 2022/10/8.
//
#include <bits/stdc++.h>
using namespace std;

struct List{
    int to, nxt;
    //    int nxt;
}edge[200005];
int head[100005];
int edgeCnt;

void read(int &x);
void addEdge(int u, int v);
pair<int, int*> findMaxDep(int u);
int* findReachableMaxDep(int u);

int main(){
    int n, k;
    read(n), read(k);

    //    Is this necessary?
    //    for(int i = 1; i <= n; i++){
    //        head[i] = nullptr;
    //        edge[i].nxt = nullptr;
    //    }

    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        addEdge(u, v);
    }

    pair<int, int*> diaA = findMaxDep(1);
    pair<int, int*> diaB = findMaxDep(diaA.first);
    int midDepA = diaB.second[diaB.first]/2 + diaB.second[diaB.first]%2;
    int midDepB = diaB.second[diaB.first] - midDepA;
    bool inMidDepA[n+1];
    for(int i = 1; i <= n; i++){
        inMidDepA[i] = (diaB.second[i] == midDepA);
    }
    int *tem = findMaxDep(diaB.first).second, midDot;
    for(int i = 1; i <= n; i++){
        if(tem[i] == midDepB && inMidDepA[i]){
            midDot = i;
            break;
        }
    }

    tem = findMaxDep(midDot).second;
    int *tem2 = findReachableMaxDep(midDot);
    int dis[n+1];
    for(int i = 1; i <= n; i++){
        dis[i] = tem2[i] - tem[i];
    }
    sort(dis+1, dis+n+1);
    int ans = dis[n-k]+1;
    printf("%d", ans);
}

pair<int, int*> findMaxDep(int u){
    static int dep[100005];
    memset(dep, -1, sizeof dep);
    int f(int u, int *dep);
    dep[u] = 0;
    int maxDot = f(u, dep);
    return {maxDot, dep};
}

int f(int u, int *dep){
    int mxDot = u;
    //    for(List *i = head[u]; i->nxt != nullptr; i = i->nxt){
    for(int pos = head[u]; pos; pos = edge[pos].nxt){
        List *i = &edge[pos];
        if(dep[i->to] == -1){
            dep[i->to] = dep[u] + 1;
            int tem = f(i->to, dep);
            if(dep[tem] > dep[mxDot]){
                mxDot = tem;
            }
        }
    }
    return mxDot;
}

int* findReachableMaxDep(int u){
    static int mxDep[100005];
    memset(mxDep, -1, sizeof mxDep);
    void f(int u, int dep, int *mxDep);
    f(u, 0, mxDep);
    return mxDep;
}

void f(int u, int dep, int *mxDep){
    mxDep[u] = dep;
    //    for(List *i = head[u]; i->nxt != nullptr; i - i->nxt){
    for(int pos = head[u]; pos; pos = edge[pos].nxt){
        List *i = &edge[pos];
        if(mxDep[i->to] == -1){
            f(i->to, dep+1, mxDep);
            mxDep[u] = max(mxDep[u], mxDep[i->to]);
        }
    }
}

void addEdge(int u, int v){
    edge[++edgeCnt] = {v, head[u]};
    head[u] = edgeCnt;
    edge[++edgeCnt] = {u, head[v]};
    head[v] = edgeCnt;
    //    head[u] = &edge[edgeCnt];
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