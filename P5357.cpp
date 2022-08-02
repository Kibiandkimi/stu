//
// Created by kibi on 2022/8/2.
//
#include <bits/stdc++.h>
using namespace std;
int n, Map[200005];
char s[200005], c[2000005];
struct node{
    int son[26];
    int flag, fail;
};
node tri[200005];
int cnt = 1;
int in[200005], ans[200005], fin_ans[200005];

void insert(int id){
    int u = 1, len = strlen(s+1);
    for(int i = 1; i <= len; i++){
        int v = s[i]-'a';
        if(!tri[u].son[v]){
            tri[u].son[v] = ++cnt;
        }
        u = tri[u].son[v];
    }
    if(!tri[u].flag){
        tri[u].flag = id;
    }
    Map[id] = tri[u].flag;
}

void GetFail(){
    queue<int> q;
    for(int & i : tri[0].son){
        i = 1;
    }
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int Fail = tri[u].fail;
        for(int i = 0; i < 26; i++){
            int & v = tri[u].son[i];
            if(!v){
                v = tri[Fail].son[i];
                continue;
            }
            tri[v].fail = tri[Fail].son[i];
            in[tri[v].fail]++;
            q.push(v);
        }
    }
}

void query(){
    int u = 1;
    for(int i = 1; c[i] != 0; i++){
        u = tri[u].son[c[i]-'a'];
        ans[u]++;
    }
}

void tp(){
    queue<int> q;
    for(int i = 0; i <= cnt; i++){
        if(!in[i]){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        fin_ans[tri[u].flag] = ans[u];
        int v = tri[u].fail;
        in[v]--;
        ans[v] += ans[u];
        if(!in[v]){
            q.push(v);
        }
    }

}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s", s+1);
        insert(i);
    }
    GetFail();
    scanf("%s", c+1);
    query();
    tp();
    for(int i = 1; i <= n; i++){
        printf("%d\n", fin_ans[Map[i]]);
    }
}