//
// Created by kibi on 2022/7/31.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int b[305];
int ans;
int cnt;
struct node{
    int u, v, w;
};
vector<node> edge;
int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}
bool cmp(node a, node b){
    return a.w < b.w;
}

int main(){
    queue<int> q;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int t;
        b[i] = i;
        //        f[i] = true;
        //        in[i] = true;
        scanf("%d", &t);
        edge.push_back({0, i, t});
        //        ans += w[i];
        //        q.push(i);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int t;
            scanf("%d", &t);
            if(j>=i){
                continue ;
            }
            edge.push_back({i, j, t});
        }
    }
    sort(edge.begin(), edge.end(), cmp);
    int se = edge.size();
    for(int i = 0; i < se && cnt < n; i++){
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if(find(b[u]) != find(b[v])){
            b[find(b[u])] = b[v];
            ans += w;
            cnt++;
        }
    }
    printf("%d", ans);
}