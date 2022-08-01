#include <bits/stdc++.h>
using namespace std;
int dfn[200005*3], low[200005*3];
bool vis[200005*3];
stack<int> s;
int n,m;
vector<int> a[200005*3];
int st = 200000;
int cnt = 1;
int num = 1;
int c[200005*3];
int ans;
void f(int x){
    dfn[x] = low[x] = cnt++;
    s.push(x);
    vis[x] = true;
    int sa = a[x].size();
    for(int i = 0; i < sa; i++){
        if(dfn[a[x][i]]==0){
            f(a[x][i]);
            low[x] = min(low[x], low[a[x][i]]);
        }else{
            if(vis[a[x][i]]){
                low[x] = min(low[x], low[a[x][i]]);
            }
        }
    }
    if(dfn[x]==low[x]){
        while(s.top()!=x){
            c[s.top()] = num;
            vis[s.top()] = false;
            s.pop();
        }
        c[x] = num++;
        vis[x] = false;
        s.pop();
    }
}
int main(){
    scanf("%d %d", &n,&m);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v+st);
        a[u+st].push_back(v+st*2);
        a[u+st*2].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(dfn[i]==0) {
            f(i);
        }
    }
    for(int i = 1; i <= n; i++){
        //        memset(dfn, 0, sizeof(dfn));
        //        memset(low, 0, sizeof(low));
        //        memset(vis, 0, sizeof(vis));
        //        memset(c, 0, sizeof(c));
        //        num = 1;
        //        cnt = 1;
        //        while(!s.empty()){s.pop();}

        if(c[i]==c[i+st]){
            ans++;
        }
    }
    printf("%d", ans);
}