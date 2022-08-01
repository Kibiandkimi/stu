//
// Created by kibi on 2021/9/29.
//
#include <bits/stdc++.h>
using namespace std;
int n;
char c[500005];
int fa[500005];
vector<int> g[500005];
long long ans, sum[500005], lst[500005];
int s[500005], top;

void f(int x){
    int t = 0;
    if(c[x]==')'){
        if(top){
            lst[x] = lst[fa[s[top]]]+1;
            t = s[top];
            top--;
        }
    }else if(c[x]=='('){
        s[++top] = x;
    }
    sum[x] = sum[fa[x]] + lst[x];
    int sg = g[x].size();
    for(int i = 0; i < sg; i++){
        f(g[x][i]);
    }
    if(t!=0){
        s[++top] = t;
    }else if(top){
        top--;
    }
}

int main(){
    cin >> n;
    scanf("%s", c+1);
    //    for(int i = 1; i <= n; i++){
    //        scanf("%1c", &c[i]);
    //    }
    for(int i = 2; i <= n; i++){
        scanf("%d", &fa[i]);
        g[fa[i]].push_back(i);
    }
    f(1);
    for(long long i = 1; i <= n; i++){
        ans ^= sum[i] * i;
    }
    printf("%lld", ans);
}