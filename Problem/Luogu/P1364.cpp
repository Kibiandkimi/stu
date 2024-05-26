//
// Created by kibi on 2021/7/12.
//
#include <bits/stdc++.h>
using namespace std;
int l[105][105],n,sum=1e9,pd[105];
struct node{
    int w,u,v;
};
struct node2{
    int s,step,sstep;
};
node a[105];
int p[105];
vector<int> r[105];
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].w >> a[i].u >> a[i].v;
    }
    for(int i = 1; i <= n; i++){
        if(a[i].u){
            r[i].push_back(a[i].u);
            r[a[i].u].push_back(i);
        }
        if(a[i].v){
            r[i].push_back(a[i].v);
            r[a[i].v].push_back(i);
        }
    }
    for(int i = 1; i <= n; i++){
        int s = 0;
        for(int j = 1; j <= n; j++){
            pd[j] = 0;
        }
        for(int j = 1; j <= n; j++){
            if(l[j][i]!=0 || i == j){
                s += l[i][j];
            }else{
                queue <node2>q;
                node2 now;
                now.s = j;
                now.step = a[j].w;
                now.sstep = 0;
                q.push(now);
                while(!q.empty()){
                    node2 t = q.front();
                    q.pop();
                    for(int k = 0; k < r[t.s].size(); k++){
                        if(pd[r[t.s][k]]!=j){
                            pd[r[t.s][k]] = j;
                            q.push(node2({r[t.s][k],t.step,t.sstep+t.step}));
                        }
                    }
                    if(t.s == i){
                        l[j][i] = t.sstep;
                        while(!q.empty()){
                            q.pop();
                        }
                    }
                }
                s+=l[j][i];
            }
        }
        sum = min(s,sum);
    }
    cout << sum;
}