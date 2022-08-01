//
// Created by kibi on 2021/10/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, S = 1, cnt[2];
bool flag = 1;
int del[100005];
int du[100005][2];
stack<int> st;
vector<int> a[100005];
void f(int x){
    int sa = a[x].size();
    for(int i = del[x]; i < sa; i=del[x]){
        del[x] = i+1;
        f(a[x][i]);
    }
    st.push(x);
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        du[u][1]++;
        du[v][0]++;
    }
    for(int i = 1; i <= n; i++){
        sort(a[i].begin(), a[i].end());
    }
    for(int i = 1; i <= n; i++){
        if(du[i][1] != du[i][0]){
            flag = 0;
        }
        if(du[i][1]-du[i][0]==1){
            cnt[1]++;
            S = i;
        }
        if(du[i][0]-du[i][1]==1){
            cnt[0]++;
        }
    }
    if((!flag)&&!(cnt[0]==cnt[1]&&cnt[0]==1)){
        printf("No");
        return 0;
    }
    f(S);
    while(!st.empty()){
        int t = st.top();
        st.pop();
        printf("%d ", t);
    }
}