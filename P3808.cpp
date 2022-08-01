//
// Created by kibi on 2022/7/11.
//
#include <bits/stdc++.h>
using namespace std;
struct tree{
    int fail, v[30], end;
}AC[1000005];
int cnt, n;
char s[1000005], t[1000005];
//int n;
void build(){
    int now = 0;
    int i = 1;
    while(s[i] != 0){
        if(!AC[now].v[s[i]-'a']){
            AC[now].v[s[i]-'a'] = ++cnt;
        }
        now = AC[now].v[s[i]-'a'];
        s[i] = 0;
        i++;
    }
    AC[now].end++;
}


int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s", s+1);
        build();
    }
    scanf("%s", t+1);

    AC[0].fail = 0;
    queue<int> q;
    for(int i = 0; i < 26; i++){
        if(AC[0].v[i]!=0){
            AC[AC[0].v[i]].fail = 0;
            q.push(AC[0].v[i]);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < 26; i++){
            if(AC[u].v[i]!=0){
                AC[AC[u].v[i]].fail = AC[AC[u].fail].v[i];
                q.push(AC[u].v[i]);
            }else{
                AC[u].v[i] = AC[AC[u].fail].v[i];
            }
        }
    }

    int now = 0, ans = 0;
    int i = 0;
    while(t[++i]!=0){
        now = AC[now].v[t[i]-'a'];
        for(int tt = now; tt&&AC[tt].end!=-1; tt = AC[tt].fail){
            ans += AC[tt].end;
            AC[tt].end = -1;
        }
    }

    printf("%d", ans);
}