//
// Created by kibi on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
long long T,n,h,r,x[1005],y[1005],z[1005],vis[1005];
//struct node{
//    double s;
//    int v;
//};
vector<long long> d[1005];
bool f(long long x){
    if(x == 1001){
        return true;
    }
    if(!d[x].size()){
        return false;
    }
    int sa = d[x].size();
    for(long long i = 0; i < sa; i++){
        if(!vis[d[x][i]]){
            vis[d[x][i]] = 1;
            if(f(d[x][i])){
                return true;
            }
        }
    }
    return false;
}
int main(){
    scanf("%lld", &T);
    while(T--){
        //        vector<int> d[1005];
        //        d->clear();
        for(int i = 0; i < 1005; i++){
            d[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        scanf("%lld %lld %lld", &n, &h, &r);
        for(int i = 1; i <= n; i++){
            scanf("%lld %lld %lld", &x[i], &y[i], &z[i]);
        }
        for(int i = 1; i <= n; i++){
            if(z[i]<=r){
                d[i].push_back(0);
                d[0].push_back(i);
            }
            if(h-z[i]<=r){
                d[i].push_back(1001);
                d[1001].push_back(i);
            }
            for(int j = i+1; j <= n; j++){
                //                d[i].push_back({sqrt(double((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]))), j});
                //                d[j].push_back({sqrt(double((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]))), i});
                if(sqrt(double((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j])))<=(double)2*r){
                    d[i].push_back(j);
                    d[j].push_back(i);
                }
            }
        }
        if(f(0)){
            printf("Yes\n");
        }else{
            printf("No\n");
        }

    }
}