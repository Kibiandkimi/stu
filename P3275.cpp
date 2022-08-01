//
// Created by kibi on 2021/8/20.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
long long s[100005],vis[100005],ss[100005];
vector<pair<int, int> > a[100005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int x,u,v;
        scanf("%d %d %d", &x, &u, &v);
        switch(x){
            // case 1:a[u].emplace_back(make_pair(v, 0));a[v].emplace_back(make_pair(u, 0));break;
            // case 2:a[v].emplace_back(make_pair(u, -1));break;
            // case 3:a[u].emplace_back(make_pair(v, 0));break;
            // case 4:a[u].emplace_back(make_pair(v, -1));break;
            // case 5:a[v].emplace_back(make_pair(u, 0));break;
            case 1:a[u].emplace_back(make_pair(v, 0));a[v].emplace_back(make_pair(u, 0));break;
            case 2:a[u].emplace_back(make_pair(v, 1));break;
            case 3:a[v].emplace_back(make_pair(u, 0));break;
            case 4:a[v].emplace_back(make_pair(u, 1));break;
            case 5:a[u].emplace_back(make_pair(v, 0));break;
        }
        if(x%2==0&&u==v){
            cout << -1;
            return 0;
        }
    }
    // for(int i = 1; i <= n; i++){
    //     s[i] = 1e10;
    // }
    // for(int i = n; i > 0; i--){
    //     a[0].emplace_back(make_pair(i, 1));
    // }
    for(int i = 1; i <= n; i++){
        a[0].emplace_back(make_pair(i, 1));
    }
    vis[0] = 1;
    queue<int> q;
    q.push(0);
    bool flag = true;
    while(!q.empty()){
        int t = q.front();
        q.pop();
        ss[t]++;
        if(ss[t]>n){
            flag = false;
            break;
        }
        vis[t] = 0;
        for(int i = 0, sa = a[t].size(); i < sa; i++){
            if(s[a[t][i].first]<s[t]+a[t][i].second){
                s[a[t][i].first] = s[t]+a[t][i].second;
                if(!vis[a[t][i].first]){
                    q.push(a[t][i].first);
                    vis[a[t][i].first] = 1;
                }
            }
        }
    }
    if(!flag){
        cout << -1;
    }else{
        long long ss = 0;
        long long mn = 1e10;
        // for(int i = 1; i <= n; i++)mn = min(mn, s[i]);
        // mn--;
        // for(int i = 1; i <= n; i++)ss+=s[i]-mn;
        for(int i = 1; i <= n; i++)ss+=s[i];
        printf("%lld", ss);
    }
}