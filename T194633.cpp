//
// Created by kibi on 2021/8/15.
//
#include <bits/stdc++.h>
using namespace std;
long long n;
long long fa[500005];
vector<long long> a[500005];
long long s[500005],yh[10005][10005];
int main(){
    cin >> n;
    for(long long i = 2; i <= n; i++){
        long long t;
        scanf("%lld", &t);
        a[t].push_back(i);
        fa[i] = t;
    }
    for(long long i = 1; i <= n; i++){
        scanf("%lld", &s[i]);
    }
    for(long long i = 1; i <= n; i++){
        for(long long j = i+1; j <= n; j++){
            yh[i][j] = yh[j][i] = s[i]^s[j];
        }
    }
    printf("0\n");
    for(long long i = 2; i <= n; i++){
        vector<long long> v;
        //        v.push_back(i);
        long long t = i;
        while(fa[t]){
            t = fa[t];
            v.push_back(t);
        }
        //        long long f = fa[i];
        long long vis[100005] = {};
        vis[i] = 1;
        queue<long long> q;
        q.push(1);
        while(!q.empty()){
            long long t = q.front();
            for(long long i = 0; i < a[t].size(); i++){
                if(!vis[a[t][i]]){
                    q.push(a[t][i]);
                    v.push_back(a[t][i]);
                    vis[a[t][i]] = 1;
                }
            }
            q.pop();
        }
        long long sv = v.size();
        long long mx = 0;
        for(long long i = 0; i < sv; i++){
            for(long long j = i+1; j < sv; j++){
                mx = max(mx, yh[v[i]][v[j]]);
            }
        }
        printf("%lld\n", mx);
    }
}