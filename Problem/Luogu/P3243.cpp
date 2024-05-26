//
// Created by kibi on 2021/10/21.
//
#include <bits/stdc++.h>
using namespace std;
int T;
int n, m, cnt[100005], tot, ans[100005];
bool flag = 0;
vector<int> a[100005];
priority_queue<int> q;
int main(){
    scanf("%d", &T);
    while(T--){
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; i++){
            a[i].clear();
        }

        tot = 0;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= m; i++){
            int u,v;
            scanf("%d %d", &u, &v);
            a[v].push_back(u);
            cnt[u]++;
            if(u == v){
                printf("Impossible!\n");
            }

        }
        if(!flag){
            for(int i = 1; i <= n; i++){
                if(!cnt[i]){
                    q.push(i);
                }
            }
            while(!q.empty()){
                int x = q.top();
                q.pop();
                ans[++tot] = x;
                int sa = a[x].size();
                for(int i = 0; i < sa; i++){
                    if(!(cnt[a[x][i]]-1)){

                        q.push(a[x][i]);
                    }
                    cnt[a[x][i]]--;
                }
            }
            if(tot < n){
                printf("Impossible!\n");
            }else{
                for(int i = n; i >= 1; i--){
                    printf("%d ", ans[i]);
                }
                printf("\n");
            }
        }

    }
}