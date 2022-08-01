//
// Created by kibi on 2022/7/11.
//
#include <bits/stdc++.h>
using namespace std;
struct tree{
    int fail, v[30], end;
}AC[20005];
int cnt, n;
//char s[1000005], t[1000005];
char s[205][105], t[1000005];
int num[205];
//int n;
void build(int id){
    int now = 0;
    int i = 1;
    while(s[id][i] != 0){
        if(!AC[now].v[s[id][i]-'a']){
            AC[now].v[s[id][i]-'a'] = ++cnt;
        }
        now = AC[now].v[s[id][i]-'a'];
        //        s[id][i] = 0;
        i++;
    }
    AC[now].end = id;
}
void reset(){
    cnt = 0;
    for(int i = 0; i < 20005; i++){
        AC[i].fail = AC[i].end = 0;
        for(int j = 0; j < 30; j++){
            AC[i].v[j] = 0;
        }
    }
    memset(num, 0, sizeof(num));
    memset(s, 0, sizeof(s));
    memset(t, 0, sizeof(t));
}

int main(){
    scanf("%d", &n);
    while(n != 0) {
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i]+1);
            build(i);
        }
        scanf("%s", t + 1);

        AC[0].fail = 0;
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (AC[0].v[i] != 0) {
                AC[AC[0].v[i]].fail = 0;
                q.push(AC[0].v[i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (AC[u].v[i] != 0) {
                    AC[AC[u].v[i]].fail = AC[AC[u].fail].v[i];
                    q.push(AC[u].v[i]);
                } else {
                    AC[u].v[i] = AC[AC[u].fail].v[i];
                }
            }
        }

        int now = 0, ans = 0;
        int i = 0;
        while (t[++i] != 0) {
            now = AC[now].v[t[i] - 'a'];
            for (int tt = now; tt; tt = AC[tt].fail) {
                if(AC[tt].end == 0){
                    continue;
                }
                ans = max(ans, ++num[AC[tt].end]);
                //                AC[tt].end = -1;
            }
        }

        printf("%d\n", ans);
        for(int i = 1; i <= n; i++){
            if(num[i] == ans){
                for(int j = 1; s[i][j] != 0; j++){
                    printf("%c", s[i][j]);
                }
                printf("\n");
            }
        }
        scanf("%d", &n);
        reset();
    }
}