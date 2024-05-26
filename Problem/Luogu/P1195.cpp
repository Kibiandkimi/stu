//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, k, ans;
struct node{
    int u, v, w;
};
int b[1005];
vector<node> edge;
bool cmp(node a, node b){
    return a.w < b.w;
}
int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge.push_back({u, v, w});
    }
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    sort(edge.begin(), edge.end(), cmp);
    int cnt = n;
    for(int i = 0; i < m; i++){
        if(find(b[edge[i].u]) != find(b[edge[i].v])){
            b[find(edge[i].u)] = b[edge[i].v];
            ans += edge[i].w;
            cnt--;
        }
        if(cnt==k){
            printf("%d", ans);
            return 0;
        }
    }
    printf("No Answer");
}