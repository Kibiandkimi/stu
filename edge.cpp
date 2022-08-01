//
// Created by kibi on 2021/7/26.
//
//edge.cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int to;
    bool w;
};
vector<node> a[100005];
//int dd(int ta, int tb){
//
//}
int op1(int ta, int tb){
    int pd[100005] = {};
    queue<int> q;
    q.push(ta);
    while(!q.empty()){
        int n;
        n = q.front();
        q.pop();
        if(n == tb){
            break;
        }
        for(int i = 0; i < a[n].size(); i++){
            if(!pd[a[n][i].to]){
                pd[a[n][i].to]=n;
                q.push(a[n][i].to);
                if(a[n][i].to==tb){
                    while(!q.empty()){
                        q.pop();
                    }
                }
            }
        }
    }
    int t = tb;
    int ls = tb;
    while(t != ta){
        for(int i = 0; i < a[t].size(); i++){
            a[t][i].w = false;
            if(a[t][i].to==pd[t]||a[t][i].to==ls){
                a[t][i].w = true;
                continue;
            }
            for(int j = 0; j < a[a[t][i].to].size(); j++){
                if(a[a[t][i].to][j].to==t){
                    a[a[t][i].to][j].w = false;
                }
            }

        }
        ls = t;
        t = pd[t];
    }
    for(int i = 0; i < a[ta].size(); i++){
        a[ta][i].w = false;
        if(a[ta][i].to==ls){
            a[ta][i].w = true;
            continue;
        }
        for(int j = 0; j < a[a[ta][i].to].size(); j++){
            if(a[a[ta][i].to][j].to==ta){
                a[a[ta][i].to][j].w = false;
            }
        }

    }
    return 0;
}
int op2(int ta, int tb){
    int pd[100005] = {};
    queue<int> q;
    q.push(ta);
    while(!q.empty()){
        int n;
        n = q.front();
        q.pop();
        if(n == tb){
            break;
        }
        for(int i = 0; i < a[n].size(); i++){
            if(!pd[a[n][i].to]){
                pd[a[n][i].to]=n;
                q.push(a[n][i].to);
                if(a[n][i].to==tb){
                    while(!q.empty()){
                        q.pop();
                    }
                }
            }
        }
    }
    int t = tb;
    int ss = 0;
    while(t != ta){
        for(int i = 0; i < a[t].size(); i++){
            if(a[t][i].to==pd[t]){
                ss+=a[t][i].w;
            }
        }
        t = pd[t];
    }
    printf("%d\n", ss);
    return 0;
}
int o(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(node({v,false}));
        a[v].push_back(node({u,false}));
    }
    for(int i = 1; i <= m; i++){
        int op,ta,tb;
        cin >> op >> ta >> tb;
        if(op == 1){
            op1(ta, tb);
        }else{
            op2(ta, tb);
        }
    }
}
int main(){
    freopen("edge.in", "r", stdin);
    freopen("edge.out", "w", stdout);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++){
        o();
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}