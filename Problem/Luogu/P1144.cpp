//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
static const int mod = 100003;
using namespace std;
int n, m;
vector<int> g[1000005];
bool vis[1000005];
int num[1000005], sum[1000005];
struct node{
    int u, s;
};
queue<int> q;

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    q.push(1);
    num[1] = 0;
    sum[1] = 1;
    vis[1] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            int v = g[u][i];
            if(!vis[v]){
                vis[v] = true;
                num[v] = num[u]+1;
                sum[v] = (sum[u]+sum[v]) % mod;
                q.push(v);
            }else if(num[v] == num[u]+1){
                sum[v] = (sum[u]+sum[v]) % mod;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n", sum[i]%mod);
    }
}